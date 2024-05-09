
#include <vector>


template <typename Vertex, typename Distance = double>
class Graph
{
public:
	struct Edge
	{
		Vertex _from;
		Vertex _to;
		Distance _distance;
	};

    //проверка-добавление-удаление вершин
    bool has_vertex(const Vertex& v) const;
    void add_vertex(const Vertex& v);
    bool remove_vertex(const Vertex& v);
    std::vector<Vertex> vertices() const;


    //проверка-добавление-удаление ребер
    void add_edge(const Vertex& from, const Vertex& to, const Distance& d);
    bool remove_edge(const Vertex& from, const Vertex& to);
    bool remove_edge(const Edge& e); //c учетом расстояния
    bool has_edge(const Vertex& from, const Vertex& to) const;
    bool has_edge(const Edge& e) const; //c учетом расстояния в Edge

    //получение всех ребер, выходящих из вершины
    std::vector<Edge> edges(const Vertex& vertex);

    size_t order() const; //порядок 
    size_t degree(const Vertex& v) const; //степень вершины


    //поиск кратчайшего пути
    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const;
    //обход
    std::vector<Vertex>  walk(const Vertex& start_vertex)const;

private:
    std::vector<Vertex> _vertices;
    std::vector<Edge> _edges;
};



template <typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_vertex(const Vertex& v) const
{
    return std::find(_vertices.begin(), _vertices.end(), v) != _vertices.end();
}

template <typename Vertex, typename Distance>
void Graph<Vertex, Distance>::add_vertex(const Vertex& v)
{
    if (!has_vertex(v))
        _vertices.push_back(v);
}

template <typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_vertex(const Vertex& v)
{
    auto it = std::find(_vertices.begin(), _vertices.end(), v);
    if (it == _vertices.end())
        return false;

    _vertices.erase(it);

    auto edges_it = _edges.begin();
    while (edges_it != _edges.end())
    {
        if (edges_it->from == v || edges_it->to == v)
        {
            _edges.erase(edges_it);
        }
        else
            edges_it++;
    }

    return true;
}

template <typename Vertex, typename Distance>
std::vector<Vertex> Graph<Vertex, Distance>::vertices() const
{
    return _vertices;
}


template <typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_edge(const Edge& e) const
{
    return std::find(_edges.begin(), _edges.end(), e) != edges.end();
}


template <typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_edge(const Vertex& from, const Vertex& to) const
{
    for (const auto &edge : _edges)
    {
        if (edge.from == from && edge.to == to)
            return true;
    }
    return false;
}


template <typename Vertex, typename Distance>
void  Graph<Vertex, Distance>::add_edge(const Vertex& from, const Vertex& to, const Distance& d)
{
    if (!has_edge({from, to, d}))
        _edges.push_back({ from, to, d });
}
