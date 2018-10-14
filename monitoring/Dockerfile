FROM ubuntu:xenial
COPY agent /opt/datadog-agent/bin/agent/
COPY probe.sh /probe.sh
COPY dist/ /opt/datadog-agent/bin/agent/dist/
RUN apt-get update \
  && apt-get install --no-install-recommends -y curl ca-certificates libpython2.7-dev
COPY datadog.yaml /etc/datadog-agent/datadog.yaml
ENV DOCKER_DD_AGENT=true \
    PATH=/opt/datadog-agent/bin/agent/:/opt/datadog-agent/embedded/bin/:$PATH

EXPOSE 8125/udp 8126/tcp

HEALTHCHECK --interval=2m --timeout=10s --retries=2 \
  CMD ["/probe.sh"]

CMD ["/opt/datadog-agent/bin/agent/agent", "start"]
