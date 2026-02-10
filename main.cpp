#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    const string DAYS[7] = {"Monday", "Tuesday", "Wednesday", "Thursday",
                           "Friday", "Saturday", "Sunday"};

    // Storage for monthly data (up to 12 months)
    const int MAX_MONTHS = 12;
    float monthlyCosts[MAX_MONTHS] = {0};
    float monthlyLitres[MAX_MONTHS] = {0};
    int monthsRecorded = 0;

    int currentDayIndex = 0;  // Start with Monday
    int currentWeek = 1;
    int currentMonth = 1;
    float totalCost = 0;
    float monthlyCost = 0;
    float monthlyLitresTotal = 0;
    float dailyLitres;
    float costPerLitre;

    // Currency symbol
    const string CURRENCY = "GHC";

    cout << "=== FUEL TRACKING PROGRAM (Currency: Ghana Cedis - " << CURRENCY << ") ===\n" << endl;

    // Continue tracking until user decides to stop
    while (currentMonth <= MAX_MONTHS) {
        string currentDay = DAYS[currentDayIndex];

        cout << "\n--- " << currentDay << " (Week " << currentWeek
             << " of Month " << currentMonth << ") ---" << endl;

        // Get input for this day
        cout << "Enter litres used: ";
        cin >> dailyLitres;
        cout << "Enter cost per litre (" << CURRENCY << "): ";
        cin >> costPerLitre;

        float dailyCost = dailyLitres * costPerLitre;
        totalCost += dailyCost;
        monthlyCost += dailyCost;
        monthlyLitresTotal += dailyLitres;

        cout << fixed << setprecision(2);
        cout << "Daily cost: " << CURRENCY << " " << dailyCost << endl;

        // Move to next day
        currentDayIndex = (currentDayIndex + 1) % 7;

        // Check if week completed
        if (currentDayIndex == 0) {
            cout << "\n=== End of Week " << currentWeek
                 << " ===" << endl;
            cout << "Week " << currentWeek << " cost: " << CURRENCY << " " << monthlyCost
                 << " (Month " << currentMonth << " so far)" << endl;
            currentWeek++;
        }

        // Check if month completed (4 weeks = 1 month)
        if (currentWeek > 4) {
            // Store monthly data
            monthlyCosts[monthsRecorded] = monthlyCost;
            monthlyLitres[monthsRecorded] = monthlyLitresTotal;
            monthsRecorded++;

            cout << "\n========================================";
            cout << "\n=== END OF MONTH " << currentMonth << " SUMMARY ===";
            cout << "\n========================================\n";
            cout << "Total litres used: " << monthlyLitresTotal << " L" << endl;
            cout << "Total monthly cost: " << CURRENCY << " " << monthlyCost << endl;
            cout << "Average cost per litre: " << CURRENCY << " "
                 << (monthlyLitresTotal > 0 ? monthlyCost/monthlyLitresTotal : 0) << endl;
            cout << "Average daily cost: " << CURRENCY << " " << monthlyCost/28.0 << endl;

            // Ask if user wants to compare with previous months
            if (monthsRecorded > 1) {
                char compareChoice;
                cout << "\nDo you want to compare with previous months? (y/n): ";
                cin >> compareChoice;

                if (compareChoice == 'y' || compareChoice == 'Y') {
                    cout << "\n=== MONTHLY COMPARISON ===" << endl;
                    cout << setw(8) << "Month"
                         << setw(18) << "Cost (" + CURRENCY + ")"
                         << setw(12) << "Litres"
                         << setw(25) << "Avg Price/L (" + CURRENCY + ")"
                         << setw(15) << "Change %" << endl;
                    cout << string(78, '-') << endl;

                    for (int i = 0; i < monthsRecorded; i++) {
                        float avgPrice = monthlyLitres[i] > 0 ?
                                        monthlyCosts[i]/monthlyLitres[i] : 0;

                        // Calculate percentage change from previous month
                        float percentChange = 0;
                        if (i > 0 && monthlyCosts[i-1] > 0) {
                            percentChange = ((monthlyCosts[i] - monthlyCosts[i-1]) /
                                           monthlyCosts[i-1]) * 100;
                        }

                        cout << setw(8) << i+1
                             << setw(18) << fixed << setprecision(2) << monthlyCosts[i]
                             << setw(12) << fixed << setprecision(1) << monthlyLitres[i]
                             << setw(25) << fixed << setprecision(3) << avgPrice
                             << setw(15) << fixed << setprecision(1) << percentChange << "%"
                             << endl;
                    }

                    // Calculate inflation rate
                    if (monthsRecorded >= 2) {
                        float firstMonthPrice = monthlyLitres[0] > 0 ?
                                               monthlyCosts[0]/monthlyLitres[0] : 0;
                        float lastMonthPrice = monthlyLitres[monthsRecorded-1] > 0 ?
                                              monthlyCosts[monthsRecorded-1]/monthlyLitres[monthsRecorded-1] : 0;

                        if (firstMonthPrice > 0) {
                            float inflationRate = ((lastMonthPrice - firstMonthPrice) /
                                                 firstMonthPrice) * 100;
                            cout << "\n=== INFLATION ANALYSIS ===" << endl;
                            cout << "Price in Month 1: " << CURRENCY << " " << firstMonthPrice << " per litre" << endl;
                            cout << "Price in Month " << monthsRecorded << ": " << CURRENCY << " " << lastMonthPrice << " per litre" << endl;
                            cout << "Inflation rate over " << monthsRecorded << " month(s): "
                                 << fixed << setprecision(1) << inflationRate << "%" << endl;

                            if (inflationRate > 0) {
                                cout << "Your fuel costs have increased by " << fixed << setprecision(1) << inflationRate << "%" << endl;
                            } else if (inflationRate < 0) {
                                cout << "Your fuel costs have decreased by " << fixed << setprecision(1) << abs(inflationRate) << "%" << endl;
                            } else {
                                cout << "Your fuel costs have remained stable" << endl;
                            }
                        }
                    }
                }
            }

            // Ask if user wants to continue to next month
            if (currentMonth < MAX_MONTHS) {
                char continueChoice;
                cout << "\nContinue to next month? (y/n): ";
                cin >> continueChoice;

                if (continueChoice == 'n' || continueChoice == 'N') {
                    break;
                }
            }

            // Reset for next month
            currentMonth++;
            currentWeek = 1;
            monthlyCost = 0;
            monthlyLitresTotal = 0;
            currentDayIndex = 0;  // Start new month on Monday
        }
    }

    // Final Summary
    cout << "\n\n========================================";
    cout << "\n=== FINAL ANNUAL SUMMARY ===";
    cout << "\n========================================\n";
    cout << fixed << setprecision(2);
    cout << "Total months recorded: " << monthsRecorded << endl;
    cout << "Total annual cost: " << CURRENCY << " " << totalCost << endl;

    if (monthsRecorded > 0) {
        float averageMonthlyCost = totalCost / monthsRecorded;
        cout << "Average monthly cost: " << CURRENCY << " " << averageMonthlyCost << endl;

        // Find best and worst months
        int bestMonth = 0, worstMonth = 0;
        for (int i = 1; i < monthsRecorded; i++) {
            if (monthlyCosts[i] < monthlyCosts[bestMonth]) bestMonth = i;
            if (monthlyCosts[i] > monthlyCosts[worstMonth]) worstMonth = i;
        }

        cout << "\nBest month (lowest cost): Month " << bestMonth+1
             << " - " << CURRENCY << " " << monthlyCosts[bestMonth] << endl;
        cout << "Worst month (highest cost): Month " << worstMonth+1
             << " - " << CURRENCY << " " << monthlyCosts[worstMonth] << endl;

        // Calculate savings if user matched best month's spending
        float potentialSavings = totalCost - (monthlyCosts[bestMonth] * monthsRecorded);
        if (potentialSavings > 0) {
            cout << "\nPotential annual savings if you maintained best month's spending: "
                 << CURRENCY << " " << potentialSavings << endl;
        }

        // Calculate total litres and average price
        float totalLitres = 0;
        for (int i = 0; i < monthsRecorded; i++) {
            totalLitres += monthlyLitres[i];
        }
        cout << "\nTotal litres consumed: " << fixed << setprecision(1) << totalLitres << " L" << endl;
        cout << "Overall average price per litre: " << CURRENCY << " "
             << fixed << setprecision(3) << (totalLitres > 0 ? totalCost/totalLitres : 0) << endl;
    }

    cout << "\nThank you for using the Fuel Tracking Program!" << endl;

    return 0;
}
