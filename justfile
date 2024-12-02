# Define a recipe to run the Python script with the day parameter
new-day day:
    uv run util/new-day.py {{day}}