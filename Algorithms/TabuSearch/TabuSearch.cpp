#include <Algorithms/TabuSearch/TabuSearch.hpp>
#include <Graph/GraphMatrix.hpp>


TabuSearch::TabuSearch(const TabuConfiguration& tabuConfig)
    : localSearch()
    , tabuList()
    , timer()
    , tabuConfiguration(tabuConfig)
    , INFINITY(-1)
{ }

TabuSearch::PathWithCost TabuSearch::findBestPossibleRoute(std::unique_ptr<GraphMatrix>& graphMatrix)
{
    std::vector<uint32_t> startRoute = localSearch.findStartingPathGreedyStyle(graphMatrix);     // Tu bedziemy zapisywac optymalne (w danej chwili) rozwiazanie
    
    timer.start();

    std::vector<uint32_t> optimalRoute;     // Tu bedziemy zapisywac optymalne (w danej chwili) rozwiazanie
    int32_t optimalRouteLength = INFINITY;            // -1 - bedziemy odtad uznawac, ze to jest nieskonczonosc ;-)
    std::vector<uint32_t> currentRoute;     // Rozpatrywane rozwiazanie

    // Wyznaczenie poczatkowego rozwiazania algorytmem zachlannym
    //currentRoute = Graph::travellingSalesmanGreedy(graph);
    currentRoute = startRoute;

    // Inicjalizacja glownej petli...
    std::vector< std::vector<uint32_t> > tabuArray;
    uint32_t currentTabuSteps = tabuConfiguration.getCadencyLength();
    int32_t stopCounter = 0;
    bool timeNotExceeded = true;

    // Rdzen algorytmu
    while(timeNotExceeded == true)
    {
        bool cheeseSupplied = true;
        bool intensification = false;

        while(cheeseSupplied == true)
        {
            std::vector<uint32_t> nextRoute;
            int32_t nextRouteLength = -1;

            std::vector<uint32_t> nextTabu(3, 0);
            nextTabu.at(0) = currentTabuSteps;

            // Generowanie sasiedztwa typu swap przez zamiane wierzcholkow
            // (wierzcholka startowego i zarazem ostatniego nie ruszamy,
            // pomijamy tez od razu aktualny wierzcholek)
            for(int32_t i = 1; i < graphMatrix->getVertexCount() - 1; i++)
            {
                for(int32_t j = i + 1; j < graphMatrix->getVertexCount(); j++)
                {
                    std::vector<uint32_t> neighbourRoute = currentRoute;

                    // Zamiana
                    uint32_t buffer = neighbourRoute.at(j);
                    neighbourRoute.at(j) = neighbourRoute.at(i);
                    neighbourRoute.at(i) = buffer;

                    uint32_t neighbourRouteLength = 0;
                    for(int32_t i = 1; i < neighbourRoute.size(); i++)
                        neighbourRouteLength += graphMatrix->getWeight(neighbourRoute.at(i - 1), neighbourRoute.at(i));

                    // Sprawdzenie, czy dany ruch nie jest na liscie tabu
                    // (dwa wierzcholki)
                    bool tabu = false;
                    for(int32_t k = 0; k < tabuArray.size(); k++)
                    {
                        if(tabuArray.at(k).at(1) == i && tabuArray.at(k).at(2) == j)
                        {
                            tabu = true;
                            break;
                        }

                        if(tabuArray.at(k).at(1) == j && tabuArray.at(k).at(2) == i)
                        {
                            tabu = true;
                            break;
                        }
                    }

                    // Kryterium aspiracji...
                    if(tabu == true && neighbourRouteLength >= optimalRouteLength)
                        // ...jezeli niespelnione - pomijamy ruch
                        continue;

                    if(nextRouteLength == -1)
                    {
                        nextRouteLength = neighbourRouteLength;
                        nextRoute = neighbourRoute;
                        nextTabu.at(1) = i;
                        nextTabu.at(2) = j;
                    }
                    else if(nextRouteLength > neighbourRouteLength)
                    {
                        nextRouteLength = neighbourRouteLength;
                        nextRoute = neighbourRoute;
                        nextTabu.at(1) = i;
                        nextTabu.at(2) = j;
                    }
                }
            }

            currentRoute = nextRoute;
            // PEA 2 Plus
            // Jan Potocki 2019

            if(optimalRouteLength == -1)
            {
                optimalRouteLength = nextRouteLength;
                optimalRoute = nextRoute;

                // Reset licznika
                stopCounter = 0;
            }
            else if(optimalRouteLength > nextRouteLength)
            {
                optimalRouteLength = nextRouteLength;
                optimalRoute = nextRoute;

                // Zaplanowanie intensyfikacji przy znalezieniu nowego optimum
                intensification = true;

                // Reset licznika
                stopCounter = 0;
            }

            // Weryfikacja listy tabu...
            int32_t tabuPos = 0;
            while(tabuPos < tabuArray.size())
            {   
                // ...aktualizacja kadencji na liscie tabu
                tabuArray.at(tabuPos).at(0)--;
                
                //...usuniecie zerowych kadencji
                if(tabuArray.at(tabuPos).at(0) == 0)
                    tabuArray.erase(tabuArray.begin() + tabuPos);
                else
                    tabuPos++;
            }

            // ...dopisanie ostatniego ruchu do listy tabu
            tabuArray.push_back(nextTabu);

            // Zliczenie iteracji
            stopCounter++;

            // Zmierzenie czasu
            timer.stop();
            if(timer.getTime() > tabuConfiguration.getTabuInterval())
                timeNotExceeded = false;

            // Sprawdzenie warunku zatrzymania
            if(tabuConfiguration.isDiversificationEnabled())
            {
                // Przy aktywowanej dywersyfikacji - po zadanej liczbie iteracji bez poprawy
                if(stopCounter >= tabuConfiguration.getNumberOfIterations() || timeNotExceeded == false)
                    cheeseSupplied = false;
            }
            else
            {
                // Przy nieaktywowanej dywersyfikacji - po uplynieciu okreslonego czasu
                if(timeNotExceeded == false)
                    cheeseSupplied = false;
            }
        }

        // Dywersyfikacja
        if(tabuConfiguration.isDiversificationEnabled())
        {
            if(intensification == true)
            {
                // Intensyfikacja przeszukiwania przez skrócenie kadencji
                // (jezeli w ostatnim przebiegu znaleziono nowe minimum)
                currentRoute = optimalRoute;
                currentTabuSteps = tabuConfiguration.getTabuInterval() / 4;
                intensification = false;
                // PEA 2 Plus
                // Jan Potocki 2019
            }
            else
            {
                // W innym przypadku wlasciwa dywersyfikacja przez wygenerowanie nowego
                // rozwiazania startowego algorytmem hybrydowym losowo-zachlannym
                currentRoute = localSearch.findStartingPathRandomly(graphMatrix);
                currentTabuSteps = tabuConfiguration.getTabuInterval();
                intensification = false;
            }
        }

        // Reset licznika iteracji przed restartem
        stopCounter = 0;
    }

    PathWithCost result;
    result.second = optimalRoute;
    result.first = optimalRouteLength;

    return result;
}
