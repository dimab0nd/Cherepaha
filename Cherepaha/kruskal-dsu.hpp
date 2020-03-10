#include <QVector>
#include <algorithm> //std::sort
#include <stdexcept>
#include <QPair>
#include <QMap>

using namespace std;
   namespace MST {
    /**
     * Поиск остовного дерева по алгоритму Краскала с использованием системы непересекающихся множеств
     * с эвристикой сжатия пути и объединеия по рангу
     * @param input Вектор с координатами вершин в том порядке, как они связаны ребрами
     * @return Одномерный вектор, содержащий ребра остовного дерева (вершина1 - вершина2)
     */
        QVector<QPair<QPair<int,int>,QPair<int,int>>> kruskal( QVector<QPair<int,int>> const &input)
		{
			class DSU {
			public:

				DSU()
				{

				};

                DSU(QVector<QPair<int,int>> const &input) : DSU() {
                    for (int i = 0; i < input.size(); i++)
                    {
                        p.insert(input[i],qMakePair(input[i],0));
                    };

                };

                QPair<int,int> get(QPair<int,int> v)
                {
                    return(v == p[v].first) ? v : (p[v].first = get(p[v].first));

                };

                void unite(QPair<int,int> a, QPair<int,int> b)
				{
					a = get(a);
					b = get(b);

					if (a != b)
                    {
                        if (p[a].second < p[b].second)
                                    swap (a, b);
                                p[b].first = a;
                                if (p[a].second == p[b].second)
                                    ++p[a].second;
                    }
                };

			protected:         
                QMap<QPair<int,int>, QPair<QPair<int,int>,int>> p; //Вершина -> ее предок, ее ранк
			};

			int n = input.size();

            QVector<QPair<QPair<int,int>,QPair<int,int>>> res;
            QVector<QPair<QPair<int,int>,QPair<int,int>>> g; //вершина 1 - вершина 2

            DSU p(input);
            for (int i = 1; i < n; i++)
            {
                QPair<int,int> a = input[i-1];
                QPair<int,int> b = input[i];

                if (p.get(a) != p.get(b))
                {
                    res.push_back(qMakePair(a,b));
                    p.unite(a, b);
                }
            }
            return res;
		}
		
    }

