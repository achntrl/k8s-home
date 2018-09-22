# README

Deploy the kube-state-metrics folder with `kubectl apply -f kube-state-metrics/`.
Then apply `datadog-serviceaccount.yaml` and `datadog-ds.yaml`

## Building the image

I rented a Scaleway `arm` VPS, cloned the [datadog-agent](https://github.com/DataDog/datadog-agent)
repo then build the agent with

```bash
# Run only once
invoke deps
# Run to build
invoke agent.build --build-exclude=systemd,cpython,jmx,zk,snmp
```

then scp the `agent` binary and the `bin/agent/dist` folder to a RP and build it
with the Dockerfile
