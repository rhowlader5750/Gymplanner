#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "log.cpp"
#include <random>
#include <iomanip>
#include <map>
#include <algorithm>
#include <iterator>


class Workout {
    public:
    string name;
    int sets;
    int reps;
    string category;
};


vector<Workout> read_workouts_from_file(const string& filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Failed to open file: " << filename << endl;
        return {};
    }

    vector<Workout> workouts;
    string line;
    while (getline(infile, line)) {
        if (line.empty()) {
            continue;  
        }

        if (line.find("Category: ") == 0) {

            string category = line.substr(10);
            while (getline(infile, line) && !line.empty()) {
                istringstream iss(line);
                string name;
                string sets_str;
                string reps_str;
                getline(iss, name, ' ');
                getline(iss, sets_str, ' ');
                getline(iss, reps_str, ' ');
                int sets = stoi(sets_str.substr(5));
                int reps = stoi(reps_str.substr(5));
                workouts.push_back({name, sets, reps, category});
            }
        }
    }

    return workouts;
}


void generateBodyWorkout(vector<Workout>& workouts, string BodyPart) {
    string bodyParts[] = {"legs", "back", "chest", "abs", "arms"};
    int numBodyParts = 5;
    bool workoutValid = false;
    int bodyPartIndex;

    while (!workoutValid) {
        if(BodyPart == "legs"){
            bodyPartIndex = 0;
        }
        else if(BodyPart == "back"){
            bodyPartIndex = 1;
        }
        else if(BodyPart == "chest"){
            bodyPartIndex = 2;
        }
        else if(BodyPart == "abs"){
            bodyPartIndex = 3;
        }
        else if(BodyPart == "arms"){
            bodyPartIndex = 4;
        }
    
        string bodyPart = bodyParts[bodyPartIndex];
        vector<Workout> bodyPartWorkouts;
        
        int totalReps = 0;

        for (const auto& workout : workouts) {
            if (workout.category == bodyPart) {
                bodyPartWorkouts.push_back(workout);
            }
        }

    
            cout << "Body workout for " << bodyPart << ":" << endl;
            while (totalReps < 20) {
                int workoutIndex = rand() % bodyPartWorkouts.size();
                Workout workout = bodyPartWorkouts[workoutIndex];
                totalReps += (workout.sets * workout.reps);
                cout << workout.name << " (" << workout.sets << " sets x " << workout.reps << " reps)" << endl;
                bodyPartWorkouts.erase(bodyPartWorkouts.begin() + workoutIndex); // remove selected exercise
            }
            workoutValid = true;
        }
    }



template<typename T>
string join(const T& v, const string& delimiter) {
    ostringstream result;
    for (auto i = v.begin(); i != v.end(); ++i) {
        if (i != v.begin()) {
            result << delimiter;
        }
        result << *i;
    }
    return result.str();
}


void generateWeekWorkoutPlan(vector<Workout>& workouts) {
    string bodyParts[] = {"legs", "back", "chest", "abs", "arms"};
    int numBodyParts = 5;
    

    map<string, string> dayBodyPartMap;
    int i = 0;
    for (const auto& bodyPart : bodyParts) {
        string day = "Day " + to_string(i+1);
        dayBodyPartMap[day] = bodyPart;
        i++;
    }

    random_device rd;
    mt19937 g(rd());


    shuffle(begin(bodyParts), end(bodyParts),g);

  
    vector<string> days;
    for (const auto& entry : dayBodyPartMap) {
        days.push_back(entry.first);
    }
    

    
    map<string, vector<Workout>> bodyPartWorkoutsMap;
    for (const auto& bodyPart : bodyParts) {
        vector<Workout> bodyPartWorkouts;
        for (const auto& workout : workouts) {
            if (workout.category == bodyPart) {
                bodyPartWorkouts.push_back(workout);
            }
        }
        bodyPartWorkoutsMap[bodyPart] = bodyPartWorkouts;
    }


    ofstream outfile("week_plan.txt");
    outfile << setw(20) << left << "Day" << setw(20) << left << "Body Part" << setw(30) << left << "Exercises" << endl;
    outfile << string(70, '-') << endl;
    for (const auto& day : days) {
        string bodyPart = dayBodyPartMap[day];
        vector<Workout> bodyPartWorkouts = bodyPartWorkoutsMap[bodyPart];
        vector<string> exerciseNames;
        int totalReps = 0;
        while (totalReps < 20) {
            int workoutIndex = rand() % bodyPartWorkouts.size();
            Workout workout = bodyPartWorkouts[workoutIndex];
            totalReps += (workout.sets * workout.reps);
            exerciseNames.push_back(workout.name);
            bodyPartWorkouts.erase(bodyPartWorkouts.begin() + workoutIndex);
        }
        outfile << setw(20) << left << day << setw(20) << left << bodyPart << setw(30) << left << join(exerciseNames, ", ") << endl;

    }
    outfile.close();

    cout << "Week plan written to file 'week_plan.txt'" << endl;
}



int main() {
    vector<Excercise> workout;

    int choice = 0;
    while (choice != 6) {
        cout << "1. Log Workout\n";
        cout << "2. Generate Body Workout\n";
        cout << "3. Write Workouts to File\n";
        cout << "4. Generate a Week Plan\n";
        cout << "5. Edit a workout\n";
        cout << "6. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        string bodyPart;

        if (choice == 1) {
            logWorkout(workout); 
        }
        else if (choice == 2){
            string bodyPart;
            cout << "Enter the body part you want to work on (legs, back, chest, abs, arms): ";
            cin >> bodyPart;
            auto workouts = read_workouts_from_file("workout.txt");
            generateBodyWorkout(workouts, bodyPart); 
        }
        else if (choice == 3){
            write_workouts_to_file(workout, "workout.txt"); 
            cout << "Workouts written to file." << endl;
        }
       
        else if (choice == 4){
            
            vector<Workout> workouts = read_workouts_from_file("workout.txt");
            generateWeekWorkoutPlan(workouts);
        }
         else if (choice == 5){
            edit_workout(workout);
        }
         else if (choice == 6){
            cout << "Exiting program." << endl;
            break;
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }

    return 0;
}






     
