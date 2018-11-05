Order

On the slaves:

~~TODO: Mount the acme.json on NFS volume~~

```bash
mkdir -p ~/k8s-home/traefik
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
kubectl apply -f traefik-pv.yml
kubectl apply -f traefik-pvc.yml
kubectl apply -f traefik-ingress-controller.yml
```

[Original source here](https://github.com/evnsio/k8s-home/tree/master/traefik)
