<?php

require 'vendor/autoload.php';

use Google\Analytics\Data\V1beta\Client\BetaAnalyticsDataClient;
use Google\Analytics\Data\V1beta\DateRange;
use Google\Analytics\Data\V1beta\Dimension;
use Google\Analytics\Data\V1beta\Metric;
use Google\Analytics\Data\V1beta\RunReportRequest;

/**
 * TODO(developer): Replace this variable with your Google Analytics 4
 *   property ID before running the sample.
 */
$property_id = 'YOUR PROPERTY ID';

// Using a default constructor instructs the client to use the credentials
// specified in GOOGLE_APPLICATION_CREDENTIALS environment variable.
putenv("GOOGLE_APPLICATION_CREDENTIALS=/your/key/directory/analytics-key.json");
$client = new BetaAnalyticsDataClient();

// Make an API call.
$request = (new RunReportRequest())
    ->setProperty('properties/' . $property_id)
    ->setDateRanges([
        new DateRange([
            'start_date' => '7daysAgo', //'2020-03-31',
            'end_date' => 'today',
        ]),
    ])
    ->setDimensions([
	new Dimension([
            //'name' => 'city',
            'name' => 'pageTitle',
        ]),
        new Dimension([
            'name' => 'fullPageUrl',
        ]),
    ])
    ->setMetrics([
	new Metric([
            'name' => 'screenPageViews', //'activeUsers',
        ])
    ]);
$response = $client->runReport($request);

// Print results of an API call.
//print 'Report result: ' . PHP_EOL;

foreach ($response->getRows() as $row) {
    print $row->getDimensionValues()[1]->getValue()
        . "\t" . $row->getMetricValues()[0]->getValue()
        . "\t" . $row->getDimensionValues()[0]->getValue() . PHP_EOL;
}
