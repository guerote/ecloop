#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

int notify(const char* url, const char* post_fields) {
    CURL *curl;
    CURLcode res;
    long response_code = 0;

    // Form data (application/x-www-form-urlencoded)

    printf("Notifying URL: %s\n", url);
    printf("Post fields: %s\n", post_fields);
    
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        // Set URL
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Set POST data
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields);

        // Follow redirects (optional)
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // Perform the request
        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(res));
        } else {
            // Get HTTP response code
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            printf("HTTP Response Code: %ld\n", response_code);

            if (response_code == 200) {
                printf("? Success: Server returned 200 OK\n");  
            } else {
                printf("? Failed: Server returned %ld\n", response_code);
            }
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}