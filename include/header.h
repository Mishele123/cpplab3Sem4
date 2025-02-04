
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>


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

    //��������-����������-�������� ������
    bool has_vertex(const Vertex& v) const;
    void add_vertex(const Vertex& v);
    bool remove_vertex(const Vertex& v);
    std::vector<Vertex> vertices() const;


    //��������-����������-�������� �����
    void add_edge(const Vertex& _from, const Vertex& _to, const Distance& d);
    bool remove_edge(const Vertex& _from, const Vertex& _to);
    bool remove_edge(const Edge& e); //c ������ �����   �����
    bool has_edge(const Vertex& _from, const Vertex& _to) const;
    bool has_edge(const Edge& e) const; //c ������ ���������� � Edge
    std::vector<Edge> edges() const { return _edges; }

    size_t order() const; //������� 
    size_t degree(const Vertex& v) const; //������� �������


    //����� ����������� ����
    std::vector<Edge> shortest_path(const Vertex& _from, const Vertex& _to) const
    {
        std::vector<Edge> path;
        std::vector<Distance> distance(_vertices.size(), std::numeric_limits<Distance>::max());
        std::vector<Vertex> prev(_vertices.size(), Vertex());
        
        distance[_from] = 0;
        prev[_from] = _from;

        for (size_t i = 0; i < _vertices.size() - 1; i++)
        {
            bool updated = false;
            for (auto& edge : _edges)
            {
                if (distance[edge._from] != std::numeric_limits<Distance>::max() &&
                    distance[edge._from] + edge._distance < distance[edge._to])
                {
                    distance[edge._to] = distance[edge._from] + edge._distance;
                    prev[edge._to] = edge._from;
                    updated = true;
                }
            }
            if (!updated)
                break;
        }

        if (distance[_to] == std::numeric_limits<Distance>::max())
        {
            return path;
        }

        Vertex current = _to;
        while (current != _from)
        {
            for (auto& edge : _edges)
            {
                if (edge._to == current && prev[current] == edge._from)
                {
                    path.emplace_back(edge);
                    current = edge._from;
                    break;
                }
            }
        }

        std::reverse(path.begin(), path.end());

        std::cout << "���������� ���������� �� " << _from << " �� " << _to << ":" << std::endl;

        for (auto& p : path)
        {
            std::cout << p._from << " - " << p._to << " = " << p._distance << std::endl;
        }

        return path;

    }


    //�����
    std::vector<Vertex> walk(const Vertex& start_vertex) const;

    void print_edges(const std::vector<Edge>& edges)
    {
        for (auto& e : edges)
        {
            std::cout << "from: " << e._from << " to: " << e._to << " distance: " << e._distance << std::endl;
        }
    }


    //��������� ���� �����, ��������� �� �������
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

template <typename Vertex, typename Distance>
size_t Graph<Vertex, Distance>::degree(const Vertex& v) const
{
    size_t count = 0;
    for (auto& edge : _edges)
    {
        if (edge._from == v || edge._to == v)
            count++;
    }
    return count;
}

template <typename Vertex, typename Distance>
std::vector<Vertex> Graph<Vertex, Distance>::walk(const Vertex& start_vertex) const
{
    std::vector<Vertex> visited;
    std::vector<size_t> dist(order(), false);
    std::queue<Vertex> q;

    dist[start_vertex] = true;
    q.push(start_vertex);

    while (!q.empty())
    {
        Vertex current = q.front();
        q.pop();

        visited.push_back(current);

        for (auto& edge : _edges)
        {
            if (edge._from == current)
            {
                if (!dist[edge._to])
                {
                    dist[edge._to] = true;
                    q.push(edge._to);
                }
            }
        }

    }

    std::cout << "---------------------------" << std::endl;
    for (auto& v : visited)
    {
        std::cout << v << std::endl;
    }
    std::cout << "---------------------------" << std::endl;
    return visited;
}


template <typename Vertex, typename Distance>
Distance average_distance(const Vertex& v, const Graph<Vertex, Distance>& graph)
{
    Distance distance = 0;
    size_t count = 0;

    for (auto& e : graph.edges())
    {
        if (e._from == v || e._to == v)
        {
            distance += e._distance;
            count++;
        }
    }

    if (count == 0)
    {
        return std::numeric_limits<Distance>::max();
    }

    return distance / count;
}

template <typename Vertex, typename Distance>
Distance distance_emergency_room(const Graph<Vertex, Distance>& graph)
{
    Vertex vertex;
    Distance max_distance = -1;

    for (auto& v : graph.vertices())
    {
        Distance average = average_distance(v, graph);

        if (average > max_distance)
        {
            max_distance = average;
            vertex = v;
        }
    }

    return vertex;
}