# README

Deploy the kube-state-metrics folder with `kubectl apply -f kube-state-metrics/`.
Run `kubectl create configmap datadogtoken --from-literal="event.tokenKey"="0"`
Then apply `secrets.yml`, `datadog-serviceaccount.yml`, `datadog-service.yml`;
`datadog-configmap.yml` and `datadog-ds.yml`

## Building the image

I rented a Scaleway `arm` VPS, cloned the [datadog-agent](https://github.com/DataDog/datadog-agent)
repo then build the agent with

```bash
git clone https://github.com/DataDog/datadog-agent.git
cd datadog-agent/Dockerfiles/agent
git checkout 6.6.0
wget https://github.com/adrienkohlbecker/datadog-agent-armv7/releases/download/6.6.0/datadog-agent_6.6.0.armv7-1_armhf.deb
sed -i s/amd64/armhf/g Dockerfile
sed -i s/"# make sure we have recent dependencies"/"RUN dpkg --add-architecture armhf\n\n# make sure we have recent dependencies"/g Dockerfile  # 🤮 maybe I should add a .patch file
# Optional but I noticed that 10s timeout on the healthcheck would reduce false negative
# sed -i s/5s/10s/g Dockerfile
```

The image can be found on dockerhub: achntrl/datadog-agent:6.6.0-beta

## TODO:

- [x] Fix an issue with the process agent (agent disabled)
- [x] Fix an issue with the networking agent (checkout on 6.6.0 before building the image. Networking agent to be included in 6.7)
- [x] Fix an issue where the master agent is constantly reading at 12MB/s (not fixed but related to https://github.com/kubernetes/kubernetes/issues/47928#issuecomment-381481244)
- [ ] Fix prometheus check
- [ ] Document how to install a custom check
