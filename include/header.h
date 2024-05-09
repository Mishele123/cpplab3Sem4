
#include <vector>
#include <algorithm>
#include <iostream>


template <typename Vertex, typename Distance = double>
class Graph
{
public:
    struct Edge
    {
        Vertex _from;
        Vertex _to;
        Distance _distance;

        Edge(const Vertex& _from, const Vertex& _to, const Distance& distance) : _from(_from), _to(_to), _distance(distance) {}

        bool operator==(const Edge& other) const 
        {
            return (_from == other._from) && (_to == other._to) && (_distance == other._distance);
        }

    };

    //проверка-добавление-удаление вершин
    bool has_vertex(const Vertex& v) const;
    void add_vertex(const Vertex& v);
    bool remove_vertex(const Vertex& v);
    std::vector<Vertex> vertices() const;


    //проверка-добавление-удаление ребер
    void add_edge(const Vertex& _from, const Vertex& _to, const Distance& d);
    bool remove_edge(const Vertex& _from, const Vertex& _to);
    bool remove_edge(const Edge& e); //c учетом расст   ояния
    bool has_edge(const Vertex& _from, const Vertex& _to) const;
    bool has_edge(const Edge& e) const; //c учетом расстояния в Edge


    size_t order() const; //порядок 
    size_t degree(const Vertex& v) const; //степень вершины


    //поиск кратчайшего пути
    std::vector<Edge> shortest_path(const Vertex& _from, const Vertex& _to) const;
    //обход
    std::vector<Vertex> walk(const Vertex& start_vertex)const;

    void print_edges(const std::vector<Edge>& edges)
    {
        for (auto& e : edges)
        {
            std::cout << "from: " << e._from << " to: " << e._to << " distance: " << e._distance << std::endl;
        }
    }


    //получение всех ребер, выходящих из вершины
    std::vector<Edge> edges(const Vertex& vertex)
    {
        std::vector<Edge> res_edges;
        for (auto &edge : _edges)
        {
            if (edge._from == vertex)
                res_edges.push_back(edge);
        }
        return res_edges;
    }


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
        if (edges_it->_from == v || edges_it->_to == v)
        {
            edges_it = _edges.erase(edges_it);
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
    return std::find(_edges.begin(), _edges.end(), e) != _edges.end();
}


template <typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_edge(const Vertex& _from, const Vertex& _to) const
{
    for (const auto& edge : _edges)
    {
        if (edge._from == _from && edge._to == _to)
            return true;
    }
    return false;
}


template <typename Vertex, typename Distance>
void  Graph<Vertex, Distance>::add_edge(const Vertex& _from, const Vertex& _to, const Distance& d)
{
    if (!has_edge({ _from, _to, d }))
        _edges.push_back({ _from, _to, d });
}


template <typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_edge(const Vertex& _from, const Vertex& _to)
{
    if (!has_edge(_from, _to))
        return false;

    for (auto it = _edges.begin(); it != _edges.end();)
    {
        if (it->_from == _from && it->_to == _to)
        {
            it = _edges.erase(it);
        }
        else
            it++;
    }
    return true;
}

template <typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_edge(const Edge& e)
{
    auto it = std::find(_edges.begin(), _edges.end(), e);
    if (it == _edges.end())
        return false;

    _edges.erase(it);

    return true;
}
template <typename Vertex, typename Distance>
size_t Graph<Vertex, Distance>::order() const
{
    return _vertices.size();
}
