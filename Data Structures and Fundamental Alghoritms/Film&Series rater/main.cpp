//Fernando Morán and Miguel Rivera

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class Film {
public:
    int id;
    string name;
    int length;
    string genre;
    int rating;

    Film(int _id, string _name, int _length, string _genre)
        : id(_id), name(_name), length(_length), genre(_genre), rating(0) {}

    virtual void print() {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Length: " << length << " minutes" << endl;
        cout << "Genre: " << genre << endl;
        cout << "Rating: " << rating << endl;
    }

};

class Series : public Film {
public:
    string title_episode;
    int season;

    Series(int _id, string _name, int _length, string _genre, string _title_episode, int _season)
        : Film(_id, _name, _length, _genre), title_episode(_title_episode), season(_season) {}

    void print() override {
        Film::print();
        cout << "Title episode: " << title_episode << endl;
        cout << "Season: " << season << endl;
    }

    bool operator==(int rating) {
        return this->rating == rating;
    }
};

void showMoviesWithRating(int rating, const vector<Film*>& films) {
    bool found = false;
    for (Film* film : films) {
        if (film->rating == rating && dynamic_cast<Series*>(film) == nullptr) {
            film->print();
            cout << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No movies found with rating " << rating << ".\n" << endl;
    }
}

int main() {
    ifstream file("data.txt");
    string line;

    getline(file, line);  // ignores 1st line, headers
    vector<Film*> films;
    int filmCount = 0;
    int seriesCount = 0;

    while (getline(file, line)) {
        istringstream iss(line);
        int id, length, season;
        string name, genre, title_episode;
        iss >> id >> name >> length >> genre;

        if (iss >> title_episode >> season) {
            Series* newSeries = new Series(id, name, length, genre, title_episode, season);
            films.push_back(newSeries);
            seriesCount++;
        } else {
            Film* newFilm = new Film(id, name, length, genre);
            films.push_back(newFilm);
            filmCount++;
        }
    }
    file.close();
    cout << "Film count: " << filmCount << endl;
    cout << "Series count: " << seriesCount << endl;
    int choice;
    while (true) {
        cout << "1. Show all movies/series" << endl;
        cout << "2. Select a movie/series and add a rating" << endl;
        cout << "3. Show movies/series with a specific rating" << endl;
        cout << "4. Show movies/series from a specific genre" << endl;
        cout << "5. Show movies with a specific rating" << endl;
        cout << "6. Show episodes of a specific series with a specific rating" << endl;
        cout << "7. Exit" << endl;
        cout << "Select choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\n";
            for (Film* film : films) {
                film->print();
                cout << "\n";
            }
        } else if (choice == 2) {
            int id, rating;
            cout << "Give the ID to rate: ";
            cin >> id;
            cout << "Enter the rating (1-5): ";
            cin >> rating;

            bool found = false;
            for (Film* film : films) {
                if (film->id == id) {
                    film->rating = rating;
                    found = true;
                    break;
                }
            }

            if (found) {
                ofstream outputFile("data.txt");
                outputFile << "id name length genre title_episode season rating" << endl;
                for (Film* film : films) {
                    if (Series* series = dynamic_cast<Series*>(film)) {
                        outputFile << film->id << " " << film->name << " " << film->length << " " << film->genre << " " << series->title_episode << " " << series->season << " " << film->rating << endl;
                    } else {
                        outputFile << film->id << " " << film->name << " " << film->length << " " << film->genre << " " << film->rating << endl;
                    }
                }
                outputFile.close();
                cout << "Rating added :)\n" << endl;
            } else {
                cout << "ID not found :(\n" << endl;
            }
        } else if (choice == 3) {
            int rating;
            cout << "Enter the rating: ";
            cin >> rating;
            cout << "\nMovies/Series with rating " << rating << ":\n" << endl;
            bool found = false;
            for (Film* film : films) {
                if (film->rating == rating) {
                    film->print();
                    cout << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "No movies/series found with rating " << rating << ".\n" << endl;
            }
        } else if (choice == 4) {
            string genre;
            cout << "Enter the genre: ";
            cin >> genre;
            cout << "\nMovies/Series from genre " << genre << ":\n" << endl;
            bool found = false;
            for (Film* film : films) {
                if (film->genre == genre) {
                    film->print();
                    cout <<"\n"<< endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "No movies/series found from genre " << genre << "." << endl;
            }
        } else if (choice == 5) {
            int rating;
            cout << "Enter the rating: ";
            cin >> rating;
            cout << "\nMovies with rating " << rating << ":\n" << endl;
            showMoviesWithRating(rating, films);
        } else if (choice == 6) {
            string seriesName;
            int rating;
            cout << "Enter the name of the series: ";
            cin >> seriesName;
            cout << "Enter the rating: ";
            cin >> rating;
            cout << "Episodes of series " << seriesName << " with rating " << rating << ":\n" << endl;
            bool found = false;
            for (Film* film : films) {
                if (Series* series = dynamic_cast<Series*>(film)) {
                    if (series->name == seriesName && *series == rating) {
                        series->print();
                        cout << "\n";
                        found = true;
                    }
                }
            }
            if (!found) {
                cout << "No episodes found for series " << seriesName << " with rating " << rating << ".\n" << endl;
            }
        } else if (choice == 7) {
            cout << "Goodbye!" << endl;
            break;
        } else {
            cout << "Please enter a valid choice." << endl;
        }
    }

    for (Film* film : films) {
        delete film;
    }
    return 0;
}