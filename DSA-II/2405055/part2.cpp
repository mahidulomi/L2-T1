#include <bits/stdc++.h>

using namespace std;

class Flight
{
public:
    string id;
    string fromCity;
    string toCity;
    int depTime;
    int arrTime;

    Flight()
    {
        id = "";
        fromCity = "";
        toCity = "";
        depTime = 0;
        arrTime = 0;
    }

    int timeToMinutes(string timeStr)
    {
        int hourDigit1 = timeStr[0] - '0';
        int hourDigit2 = timeStr[1] - '0';
        int totalHours = hourDigit1 * 10 + hourDigit2;

        int minuteDigit1 = timeStr[3] - '0';
        int minuteDigit2 = timeStr[4] - '0';
        int totalMinutes = minuteDigit1 * 10 + minuteDigit2;

        int totalTime = (totalHours * 60) + totalMinutes;
        return totalTime;
    }

    void setFlightData(string fId, string fCity, string tCity, string dStr, string aStr)
    {
        id = fId;
        fromCity = fCity;
        toCity = tCity;
        depTime = timeToMinutes(dStr);
        arrTime = timeToMinutes(aStr);
    }

    bool canConnectTo(Flight &nextFlight)
    {
        if (toCity != nextFlight.fromCity)
        {
            return false;
        }

        int requiredTime = arrTime + 180;
        if (requiredTime <= nextFlight.depTime)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class AirlineScheduler
{
public:
    int totalFlights;
    int totalNodes;
    int sourceNode;
    int sinkNode;
    vector<Flight> flights;
    vector<vector<int>> capacity;
    vector<vector<int>> flow;
    vector<vector<int>> adjList;

    bool bfs(vector<int> &parent)
    {
        vector<bool> visited(totalNodes, false);
        queue<int> q;

        q.push(sourceNode);
        visited[sourceNode] = true;
        parent[sourceNode] = -1;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int v : adjList[u])
            {

                if (!visited[v] && capacity[u][v] > 0)
                {
                    visited[v] = true;
                    parent[v] = u;

                    if (v == sinkNode)
                    {
                        return true;
                    }

                    q.push(v);
                }
            }
        }

        return false;
    }

    AirlineScheduler(int fCount)
    {
        totalFlights = fCount;
        flights.resize(totalFlights);

        sourceNode = 0;
        sinkNode = 2 * totalFlights + 1;
        totalNodes = 2 * totalFlights + 2;

        capacity.assign(totalNodes, vector<int>(totalNodes, 0));
        flow.assign(totalNodes, vector<int>(totalNodes, 0));
        adjList.resize(totalNodes);
    }

    void addFlight(int index, string id, string from, string to, string dep, string arr)
    {
        flights[index].setFlightData(id, from, to, dep, arr);
    }

    void addEdge(int u, int v, int cap)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        capacity[u][v] = cap;
    }

    void buildGraph()
    {

        for (int i = 0; i < totalFlights; i++)
        {
            int u = sourceNode;
            int v = i + 1;
            addEdge(u, v, 1);
        }

        for (int i = 0; i < totalFlights; i++)
        {
            int u = totalFlights + i + 1;
            int v = sinkNode;
            addEdge(u, v, 1);
        }

        for (int i = 0; i < totalFlights; i++)
        {
            for (int j = 0; j < totalFlights; j++)
            {
                if (i != j)
                {
                    bool possible = flights[i].canConnectTo(flights[j]);
                    if (possible == true)
                    {
                        int u = i + 1;
                        int v = totalFlights + j + 1;
                        addEdge(u, v, 1);
                    }
                }
            }
        }
    }

    int computeMaxMatching()
    {
        int maxFlow = 0;
        vector<int> parent(totalNodes);

        while (bfs(parent) == true)
        {
            int pathFlow = INT_MAX;

            int v = sinkNode;
            while (v != sourceNode)
            {
                int u = parent[v];
                pathFlow = min(pathFlow, capacity[u][v]);
                v = parent[v];
            }

            v = sinkNode;
            while (v != sourceNode)
            {
                int u = parent[v];
                capacity[u][v] = capacity[u][v] - pathFlow;
                capacity[v][u] = capacity[v][u] + pathFlow;

                flow[u][v] = flow[u][v] + pathFlow;
                flow[v][u] = flow[v][u] - pathFlow;

                v = parent[v];
            }

            maxFlow = maxFlow + pathFlow;
        }

        return maxFlow;
    }

    void solveAndPrint()
    {
        buildGraph();

        int maxMatching = computeMaxMatching();
        int minAircraft = totalFlights - maxMatching;

        cout << "Number of Aircraft: " << minAircraft << "\n";

        vector<int> nextFlight(totalFlights, -1);
        vector<bool> hasIncomingEdge(totalFlights, false);

        for (int i = 0; i < totalFlights; i++)
        {
            for (int j = 0; j < totalFlights; j++)
            {
                int u = i + 1;
                int v = totalFlights + j + 1;

                if (flow[u][v] == 1)
                {
                    nextFlight[i] = j;
                    hasIncomingEdge[j] = true;
                }
            }
        }

        int aircraftCount = 1;
        for (int i = 0; i < totalFlights; i++)
        {
            if (hasIncomingEdge[i] == false)
            {
                cout << "Aircraft " << aircraftCount << ": " << flights[i].id;
                aircraftCount = aircraftCount + 1;

                int current = i;
                while (nextFlight[current] != -1)
                {
                    current = nextFlight[current];
                    cout << " -> " << flights[current].id;
                }
                cout << "\n";
            }
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int F;
    if (!(cin >> F))
    {
        return 0;
    }

    AirlineScheduler scheduler(F);

    for (int i = 0; i < F; i++)
    {
        string id, from, to, dep, arr;
        cin >> id >> from >> to >> dep >> arr;
        scheduler.addFlight(i, id, from, to, dep, arr);
    }

    scheduler.solveAndPrint();

    return 0;
}