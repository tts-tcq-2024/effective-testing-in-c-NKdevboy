#include <stdio.h>
#include <assert.h>

int alertFailureCount = 0;

typedef int (*networkAlertStub)(float);
networkAlertStub GlobalNetworkAlertMork;
float CurrentCelcius=0;

int networkAlertmock(float celcius) {
    CurrentCelcius = celcius;
    return 500;
}

void alertInCelcius(float farenheit) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = GlobalNetworkAlertMork(celcius);
    if (returnCode != 200) {
        // non-ok response is not an error! Issues happen in life!
        // let us keep a count of failures to report
        // However, this code doesn't count failures!
        // Add a test below to catch this bug. Alter the stub above, if needed.
        alertFailureCount += 0;
    }
}

int main() {
    GlobalNetworkAlertMork = &networkAlertmock;
    alertInCelcius(400.5);
    assert(CurrentCelcius == 204.72222); 
    alertInCelcius(303.6);
    assert(CurrentCelcius == 150.88889);
    assert(alertFailureCount == 2);
    
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
