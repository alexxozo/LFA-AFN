#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

/**
 *  Stare represents the data structure used for a state.
 *  It contains an vector that stores a list of transitions.
 *  Say you have the state '1' that goes to '2' by the letter 'a'
 *  then you will have the vector for state '1' = [('a', 2)]
 *
 */
struct Stare {
    vector<pair<char, int> > listaTranzitii;
};

/**
 *
 * @param nrStari is an integer representing the number of states of the machine
 * @param stari is an array used to store all the states of the machine
 * @param nrStariFinale is an integer representing the number of final states
 * @param stariFinale is an array of ints used to store all final states of the machine
 * The purpose of the function is to read the machine states and transitions from "date.in"
 */
void citireAutomat(int &nrStari, Stare *&stari, int &nrStariFinale, int *&stariFinale) {
    int indexStareInceput, indexStareSfarsit, nrTranzitii;
    char literaTranzitie;
    ifstream f("..//date.in");

    f >> nrStari >> nrTranzitii >> nrStariFinale;
    stariFinale = new int[nrStariFinale];
    for (int i = 0; i < nrStariFinale; i++) f >> stariFinale[i];

    stari = new Stare[nrStari];

    for (int i = 0; i < nrTranzitii; i++) {
        f >> indexStareInceput >> literaTranzitie >> indexStareSfarsit;

        stari[indexStareInceput].listaTranzitii.push_back(make_pair(literaTranzitie, indexStareSfarsit));
    }
}

/**
 *
 * @param nrStari is an integer representing the number of states of the machine
 * @param stari is an array used to store all the states of the machine
 * @param nrStariFinale is an integer representing the number of final states
 * @param stariFinale is an array of ints used to store all final states of the machine
 * The purpose of the function is to print to the console the array of states and every
 * transition as they are stored in memory.
 */
void afisareAutomat(int nrStari, Stare *stari, int nrStariFinale, int *stariFinale) {
    for (int i = 0; i < nrStari; i++) {
        cout << i << ":";
        for (int j = 0; j < stari[i].listaTranzitii.size(); j++) {
            cout << "(" << stari[i].listaTranzitii.at(j).first << ", " << stari[i].listaTranzitii.at(j).second << ") ";
        }
        cout << endl;
    }

    cout << "Stari finale: ";
    for (int i = 0; i < nrStariFinale; i++) {
        cout << stariFinale[i];
    }
}


/**
 *
 * @param indexStareActuala is an integer representing the actual state of the machine
 * @param cuvant is a *char that stores the current word
 * @param stari is an array of states that stores all the states of the machine
 * @param nrStariFinale is an integer representing the number of final states of the machine
 * @param stariFinale is an array of ints that stores all the final states of the machine
 * @return returns true if the word is acceptes, false otherwise
 */
bool AFN(int indexStareActuala, string cuvant, Stare *stari, int nrStariFinale, int *stariFinale) {

    /// if the word array is empty then verify if the current state is also a final one
    if (cuvant[0] == NULL) {
        int i;
        for (i = 0; i < nrStariFinale; i++) {
            if (indexStareActuala == stariFinale[i])
                return true;
        }
        if (i == nrStariFinale)
            return false;
    }

    /// loops through all the coonections of the current state
    for (int i = 0; i < stari[indexStareActuala].listaTranzitii.size(); i++) {
        /// if the current word's first letter is in any of the transitions then go to that state
        /// it also prints the path from one state to another
        if (cuvant[0] == stari[indexStareActuala].listaTranzitii.at(i).first) {
            char temp = cuvant[0];
            cuvant.erase(cuvant.begin(), cuvant.begin() + 1);

            cout << indexStareActuala << " " << stari[indexStareActuala].listaTranzitii.at(i).second << endl;

            indexStareActuala = stari[indexStareActuala].listaTranzitii.at(i).second;
            if (AFN(indexStareActuala, cuvant, stari, nrStariFinale, stariFinale)) {
                return true;
            }

            cuvant.insert(cuvant.begin(), temp);
        }
    }

    return false;


}

int main() {
    int nrStari, *stariFinale, nrStariFinale;
    Stare *stari;

    citireAutomat(nrStari, stari, nrStariFinale, stariFinale);

    cout << AFN(0, "abbbac", stari, nrStariFinale, stariFinale);

}