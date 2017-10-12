#include <string>
#include <vector>
#include <algorithm>
std::vector<int> get_route(std::string key, int n, int algo, int nroutes) {
    std::vector<int> routes;
    // Key based grouping

    std::hash<std::string> hasher;
    long hashed = hasher(key);
    int route  = abs(hashed % n);
    routes.push_back(route);
    // Broadcast
    if(algo==2) {
        for(int i =0, i < n; i++) {
            if(i!=routes.back()) {
                routes.push_back(i);
            }
        }
    }
    //Multicast
    else if (algo == 3) {
	
    }

}

