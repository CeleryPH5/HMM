#include <string>
using namespace std;


double prCharGivenCharOfState(char charGenerated, char charOfTheState);
/************************************************************************/
//Calculate and return the probability of charGenerated actually typed
//given charOfTheState as the underlying cognitive state. 
/************************************************************************/

void getPrTableForPossibleInitialStates(double prTable[], int sizeOfTable);
/************************************************************************/
//Calculate for each actual cognitive state in a word of sizeOfTable characters,
//	the probability of that cognitive state being the actual first cognitive state
//	when the user types the word.
//Store these prbabilities in the prTable array.
/************************************************************************/

void getPrTableForPossibleNextStates
(double transitionPrTable[], int sizeOfTable, int currentState);
/************************************************************************/
//Calculate for each actual cognitive state in a word of sizeOfTable-1 characters,
//	the transition probability of that cognitive state being the next cognitive state
//	given currentState as the current state.
//Store these prbabilities in the transitionPrTable[] array.
/************************************************************************/


void setParametersSpellingModel();
/************************************************************************/
//Reset the parameters of the spelling model
/************************************************************************/

void displayParametersSpellingModel();
/************************************************************************/
//Display the parameters of the spelling model
/************************************************************************/

void setParametersKbModel();
/************************************************************************/
//Reset the parameters of the keyboard model
/************************************************************************/


void displayParametersKbModel();
/************************************************************************/
//Display the parameters of the keyboard model
/************************************************************************/

void typeOneWord(char word[], char output[], bool traceON = false, int maxOutput = 100) {
	int wordLen = strlen(word);
	int currentState = 0; // Start state
	int outputIndex = 0;
	output[outputIndex++] = '\0'; // Null-terminate the output array

	// Transition probability table
	double* transitionPrTable = new double[wordLen + 1];

	while (currentState < wordLen && outputIndex < maxOutput - 1) {
		getPrTableForPossibleNextStates(transitionPrTable, wordLen + 1, currentState);

		// Simulate the next state based on transition probabilities
		double randVal = (double)rand() / RAND_MAX;
		double cumulative = 0.0;
		int nextState = currentState;

		for (int i = 0; i <= wordLen; i++) {
			cumulative += transitionPrTable[i];
			if (randVal <= cumulative) {
				nextState = i;
				break;
			}
		}

		if (nextState == currentState) {
			// Repeat the same state
			continue;
		}
		else if (nextState == wordLen) {
			// End state
			break;
		}
		else {
			// Move to the next character
			output[outputIndex++] = word[nextState];
			if (traceON) {
				cout << "Transition from state " << currentState << " to state " << nextState
					<< " (typed '" << word[nextState] << "')" << endl;
			}
			currentState = nextState;
		}
	}

	output[outputIndex] = '\0'; // Null-terminate the output array

	if (traceON) {
		cout << "Final output: " << output << endl;
	}

	delete[] transitionPrTable;
}
