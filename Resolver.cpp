#include "Resolver.h"

void Resolver::resolver(std::vector<FuncPtr>& gFuncs, const Properties& vectorx, FuncCPtr fFunc)
{
    std::vector<bool> activeFuncs;
    std::set<size_t> I0;
    for (size_t i = 0; i < gFuncs.size(); i++) {
        double res = gFuncs[i]->calculate(vectorx);
        if(Approximate<double>::lessEqual(res, 0))
            // если ограничение работает как равенство, то ограничение активное
            if(Approximate<double>::equal(res, 0)) {
                activeFuncs.push_back(true);
                I0.insert(i);
            }
            // в противном случае неактивное
            else
                activeFuncs.push_back(false);
        else {
            std::cout << "x is invalid plan" << std::endl;
            return;
        }
    }

    // посчитаем количество активных функций
    int n = I0.size();

    std::vector<Matrix> gVectors;

    for(size_t i = 0; i < gFuncs.size(); i++) {
        if (!activeFuncs[i])
            continue;
        Matrix temp(1, vectorx.size());
        for(size_t j = 0; j < vectorx.size(); j++) {
            temp[0][j] = gFuncs[i]->derivative("x" + std::to_string(j + 1))->calculate(vectorx);
            std::cout << "derivative from " << "x" + std::to_string(j + 1) << ": " << gFuncs[i]->derivative("x" + std::to_string(j + 1))->getInf() << std::endl;
        }
        gVectors.push_back(temp);
    }

    Matrix fVector(1, vectorx.size());
    for (size_t i = 0; i < vectorx.size(); i++) {
         fVector[0][i] = fFunc->derivative("x" + std::to_string(i + 1))->calculate(vectorx);
    }

    fVector.transpose();
    // Это для метода Гаусса
    // Мы переносим числа в правую сторону, а слева остаются переменные с коэффициентами
    std::cout << "fVector:\n" << fVector << std::endl;
    for (size_t i = 0; i < vectorx.size(); i++)
        fVector[i][0] *= -1;

    for (size_t i = 0; i < gVectors.size(); i++) {
        gVectors[i].transpose();
        std::cout << "gVectors[" << i << "]:\n" << gVectors[i] << std::endl;
    }

    SquareMatrix A(n);

    // Далее идет очень занимательных два блока

    // здесь происходит "оптимизация" для метода Гаусса
    // если элемент из неактивной части, то мы его просто не добавляем
    for (size_t i = 0; i < gVectors.size(); i++)
            for (int j = 0, vectorIndex = 0; j < gVectors[i].getM(); j++)
                if (activeFuncs[j]) {
                    A[vectorIndex][i] = gVectors[i][vectorIndex][0];
                    vectorIndex++;
                }

    Matrix customFVector(n, 1);
    for (size_t i = 0, vectorIndex = 0; i < activeFuncs.size(); i++)
        if (activeFuncs[i]) {
            customFVector[vectorIndex] = fVector[i];
            vectorIndex++;
        }

    std::cout << "A:\n" << A << std::endl;

    Matrix lambdasVector = GaussMethod::method(A, fVector);

    std::cout << "lambdaVector:\n" << lambdasVector << std::endl;

    bool optimal = true;
    for (int i = 0; i < n; i++)
        if (Approximate<double>::less(lambdasVector[i][0], 0)) {
            std::cout << "lambda" << i << " is negative, vector x is not optimal" << std::endl;
            optimal = false;
            break;
        }
    if (optimal) {
        std::cout << "vector x is optimal" << std::endl;
        return;
    }

    std::set<int> J0;
    for(size_t i = 0; i < vectorx.size(); i++)
        if(Approximate<double>::equal(vectorx.at("x" + std::to_string(i + 1)), 0))
            J0.insert(i);

    // Кол-во gi(x) (I0.size) + vectorx.size() условий с d со * вверху + vectorx.size() условий с d со * внизу
    Matrix c(1, n + 2 * vectorx.size());
    for (int i = 0; i < fVector.getM(); i++)
        c[0][i] = fVector[i][0]; // минус, так как конвертируем из задачи минимизации в задачу максимизации

    std::cout << "\nc\n" << c << std::endl << std::endl;

    // заполняем матрицу элементами из gVectors
    Matrix As(n + vectorx.size(), n + 2 * vectorx.size());
    for(size_t i = 0; i < I0.size(); i++)
        for(int j = 0; j < gVectors[i].getM(); j++)
            As[i][j] = gVectors[i][j][0];

    for (size_t i = 0; i < vectorx.size(); i++) {
        As[i + vectorx.size()][i] = 1;
    }
    for(size_t i = 0; i < 2 * vectorx.size(); i++)
        As[i][i + vectorx.size()] = 1;
    std::cout << "A for simplex method\n" << As << std::endl;

    Matrix d_low(1, vectorx.size());
    for (size_t i = 0; i < vectorx.size(); i++)
        // если не входит в J0, то ставим -1, в противном случае 0, который стоит по умолчанию
        if (J0.find(i) == J0.end())
            d_low[0][i] = -1;

    std::cout << "d_low\n" << d_low << std::endl;
    d_low.transpose();
    A.transpose();
    Matrix b = Matrix(A) * d_low;
    A.transpose();
    b.transpose();
    d_low.transpose();
    b.resize(1, b.getN() + d_low.getN());
    for (int i = 0; i < d_low.getN(); i++)
        b[0][i + vectorx.size()] = 1 - d_low[0][i]; // 1, так как d_up всегда состоит из единиц
    std::cout << "b\n" << b << std::endl;
    b.transpose();

    std::set<int> Jb;
    for (int i = n; i < As.getN(); i++)
        Jb.insert(i);
    std::cout << "Jb: " << Jb << std::endl;

    std::vector<double> l = SimplexMethod::calculateXVector(As, Jb, b);
    std::cout << "l: " << l << std::endl;

    bool exist;
    SimplexMethod::resolveOptimal(As, c, l, Jb, exist);
    if (!exist) {
        std::cout << "I can not find optimal l" << std::endl;
        return;
    }
    l.resize(vectorx.size());
    for (size_t i = 0; i < vectorx.size(); i++)
        l[i] += d_low[0][i];
    std::cout << "l: " << l << std::endl;

    const Properties vectorXWithLid{{"x1_lid", 1}, {"x2_lid", 0}, {"x3_lid", 0}}; // на бумаге подобрал

    Matrix deltaX(1, vectorx.size());
    for (size_t i = 0; i < vectorx.size(); i++)
        deltaX[0][i] = vectorXWithLid.at("x" + std::to_string(i + 1) + "_lid") - vectorx.at("x" + std::to_string(i + 1));

    double alpha = getAlpha(fVector, Matrix(1, l.size(), {l}), deltaX);

    Matrix vectorXStar(1, vectorx.size());
    for (size_t i = 0; i < vectorx.size(); i++)
        vectorXStar[0][i] = vectorx.at("x" + std::to_string(i + 1));

    //std::cout << "test\n" << vectorXStar + (Matrix(1, l.size(), {l}) + deltaX * alpha) * 0.5 << std::endl;
    //std::cout << getT(vectorXStar, Matrix(1, l.size(), {l}), deltaX, fFunc->calculate(vectorx), fFunc, gFuncs, alpha) << std::endl;
    std::cout << vectorXStar << std::endl << vectorXStar * 0.1 << std::endl;
}

double Resolver::getAlpha(Matrix fVector, Matrix l0, Matrix deltaX)
{
    fVector.transpose();
    l0.transpose();
    deltaX.transpose();
    Matrix temp1 = fVector * l0;
    Matrix temp2 = fVector * deltaX;
    double alpha = - temp1[0][0] / temp2[0][0];
    return alpha - alpha * 0.1; // Знак строгий, я решил почему бы не взять 90% от альфа, которая подошла бы для уравнения
}

double Resolver::getT(Matrix vectorXStar, Matrix l0, Matrix deltaX, double fRes, FuncCPtr fFunc, std::vector<FuncPtr> gFuncs, double alpha)
{
    for (int i = 1; i < 1000; i++) {
        Properties tmp = getXt(vectorXStar, l0, deltaX, 0.1 * i, alpha);
        if (Approximate<double>::less(fFunc->calculate(tmp), fRes)) {
            bool isNotOkay = false;
            for (FuncCPtr gFunc : gFuncs) {
                if (Approximate<double>::greater(gFunc->calculate(tmp), 0)) {
                    isNotOkay = true;
                    break;
                }
            }
            if (!isNotOkay)
                return 0.1 * i;
        }
    }
    return -1;
}

Properties Resolver::getXt(Matrix vectorXStar, Matrix l0, Matrix deltaX, double t, double alpha)
{
    Matrix xt = vectorXStar + (l0 + deltaX * alpha) * t;
    Properties xtProps;
    for(int i = 0; i < xt.getN(); i++)
        xtProps["x" + std::to_string(i + 1)] = xt[0][i];
    return xtProps;
}
