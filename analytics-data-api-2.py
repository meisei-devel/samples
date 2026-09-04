from google.analytics.data_v1beta import BetaAnalyticsDataClient
from google.analytics.data_v1beta.types import (
    DateRange,
    Dimension,
    Metric,
    RunReportRequest,
)
from google.protobuf import json_format
import os
import json

os.environ['GOOGLE_APPLICATION_CREDENTIALS'] = "/virtual/hogeuser/analytics_ga4/analytics-key.json"
GA4_PROPERTY_ID = "111222333"

def sample_run_report(property_id=GA4_PROPERTY_ID):
    """Runs a simple report on a Google Analytics 4 property."""
    # TODO(developer): Uncomment this variable and replace with your
    #  Google Analytics 4 property ID before running the sample.
    # property_id = "YOUR-GA4-PROPERTY-ID"

    # Using a default constructor instructs the client to use the credentials
    # specified in GOOGLE_APPLICATION_CREDENTIALS environment variable.
    client = BetaAnalyticsDataClient()

    request = RunReportRequest(
        property=f"properties/{property_id}",
        dimensions=[Dimension(name="pageTitle"), Dimension(name="fullPageUrl")],
        metrics=[Metric(name="screenPageViews")],
        date_ranges=[DateRange(start_date="yesterday", end_date="today")],
    )
    response = client.run_report(request)

    #json_response = json_format.MessageToJson(response._pb)
    json_response = json_format.MessageToDict(response._pb)
    print(json.dumps(json_response, indent=2, ensure_ascii=False))

    print("Report result:")
    for row in response.rows:
        print(row.dimension_values[0].value + "\t" + row.dimension_values[1].value + "\t" + row.metric_values[0].value)

sample_run_report()
