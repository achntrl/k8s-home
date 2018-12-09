FROM python:alpine3.7

RUN pip install requests datadog

COPY get_velibs.py get_velibs.py

CMD ["python", "get_velibs.py"]

