#include<vector>
#include<pair>
class Graph
{
private:
    int m_V;
    int m_E;
    vector<vector<int> > m_vecAdj;
    
public:
    Graph(int V)
    {
        m_V = V;
        m_E = 0;
        vector<int> iVec;
        for(int i = 0; i< V; i++)
        {
            iVec.clear();
            iVec.push_back(i);
            m_vecAdj.push_back(iVec);
        }
    }
    Grap(int V,int E, pair<int,int> edge[])
    {
        m_V = V;
        m_E = E;
        
        vector<int> iVec;
        for(int i = 0; i< V; i++)
        {
            iVec.clear();
            iVec.push_back(i);
            m_vecAdj.push_back(iVec);
        }
        
        for(int i = 0; i < E; i++)
        {
            m_vecAdj[edge[i].first].push_back(edge[i].second);
        }
    }

    int GetVsize()
    {
        return m_V;
    }
    int GetEdgeSize()
    {
        return m_E;
    }     
}
