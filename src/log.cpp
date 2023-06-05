#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm> 

using namespace std;

class Excercise 
{
    public:

    string category;
    int sets;
    int reps;
    string name;
};

void logWorkout(vector<Excercise>& workouts) {
    Excercise newWorkout;

    cout << "Enter the category of your workout (legs, back, chest, abs, or arms): ";
    cin >> newWorkout.category;


    while (newWorkout.category != "legs" && newWorkout.category != "back"
           && newWorkout.category != "chest" && newWorkout.category != "abs"
           && newWorkout.category != "arms") {
        cout << "Invalid category. Please enter a valid category (legs, back, chest, abs, or arms): ";
        cin >> newWorkout.category;
    }

    cout << "Enter the sets it took to complete your workout: ";
    cin >> newWorkout.sets;

    cout << "Enter the repetitions it took to complete your set: ";
    cin >> newWorkout.reps;

    cout << "Enter the name of your workout: ";
    cin >> newWorkout.name;

    for (const auto& workout : workouts) {
        if (workout.category == newWorkout.category && workout.name == newWorkout.name) {
            cout << "A workout with the same name already exists in this category. Please enter a different name: ";
            cin >> newWorkout.name;
        }
    }

    workouts.push_back(newWorkout);


    int count = 0;
    for (const auto& workout : workouts) {
        if (workout.category == newWorkout.category) {
            count++;
        }
    }
    if (count < 3) {
        cout << "Warning: There are only " << count << " exercises for " << newWorkout.category << ". It is recommended to have at least 3 exercises per body part." << endl;
    }
}




void write_workouts_to_file(vector<Excercise>& workouts, const string& filename) {
    ofstream outfile(filename);

    map<string, vector<Excercise>> workouts_by_category;
    for (const auto& workout : workouts) {
        workouts_by_category[workout.category].push_back(workout);
    }

    for (const auto& category_workouts : workouts_by_category) {
        outfile << "Category: " << category_workouts.first << endl;
        for (const auto& workout : category_workouts.second) {
            outfile << workout.name << " Sets:" << workout.sets << " Reps:" << workout.reps << endl;
        }
        outfile << endl;
    }

    
    outfile.close();
}

void edit_workout(vector<Excercise>& workouts) {
    
    string category;
    string name;
    cout << "Enter the category of the workout you want to edit: ";
    getline(cin, category);
    cout << "Enter the name of the workout you want to edit: ";
    getline(cin, name);

    auto it = find_if(workouts.begin(), workouts.end(), [&](const Excercise& w) {
        return w.category == category && w.name == name;
    });

    if (it != workouts.end()) {
       
        cout << "Enter the new number of sets: ";
        int sets;
        cin >> sets;
        it->sets = sets;

        cout << "Enter the new number of reps: ";
        int reps;
        cin >> reps;
        it->reps = reps;

        cout << "Workout " << name << " in category " << category << " has been updated." << endl;
    } else {
        
        cout << "Workout " << name << " in category " << category << " not found." << endl;
    }
}

