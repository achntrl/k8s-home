FROM python:alpine3.7

RUN pip install requests datadog apscheduler pytz JSON-log-formatter

COPY get_velibs.py get_velibs.py

CMD ["python", "get_velibs.py"]

