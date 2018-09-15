Order

On the slaves:

```bash
rm ~/k8s-home/traefik/acme.json
touch ~/k8s-home/traefik/acme.json
sudo chmod 600 ~/k8s-home/traefik/acme.json
```

https://github.com/jcmoraisjr/ingress/blob/master/docs/examples/auth/basic/README.md

To generate a basic auth

```
kubectl create secret generic traefik-dashboard-auth --from-file=auth -n kube-system
```

```bash
kubectl apply -f secrets.yml
kubectl apply -f traefik-rbac.yml
kubectl apply -f traefik-config.yml
kubectl apply -f traefik-dashboard.yml
kubectl apply -f traefik-ingress-controller.yml
```
