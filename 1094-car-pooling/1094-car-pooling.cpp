class Solution {
private:
    struct Compare {
        bool operator()(pair<int, int> const& first, pair<int, int> const& second) {
            return first.first > second.first;
        }
    };

public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        vector<vector<int>>::size_type n = trips.size();
        priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> toPQ{};

        sort(trips.begin(), trips.end(), [](vector<int> const& first, vector<int> const& second) {
            return first[1] < second[1];
        });

        int takenSeats = 0;
        for (vector<vector<int>>::size_type i = 0; i < n; ++i) {
            int distTraveled = trips[i][1];
            int newPassengers = trips[i][0];
            int arrivalSpot = trips[i][2];

            while (!toPQ.empty() && toPQ.top().first <= distTraveled) {
                takenSeats -= toPQ.top().second;
                toPQ.pop();
            }

            int availableSeats = capacity - takenSeats;
            if (availableSeats < newPassengers) {
                return false;
            } else {
                toPQ.push({arrivalSpot, newPassengers});
                takenSeats += newPassengers;
            }
        }

        return true;
    }
};