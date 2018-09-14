Order

On the slaves:

```bash
rm ~/k8s-home/traefik/acme.json
touch ~/k8s-home/traefik/acme.json
sudo chmod 600 ~/k8s-home/traefik/acme.json
```

https://github.com/jcmoraisjr/ingress/blob/master/docs/examples/auth/basic/README.md

kubectl create secret generic traefik-dashboard-auth --from-file=auth -n kube-system

k apply -f secrets.yml
k apply -f traefik-rbac.yml
k apply -f traefik-config.yml
k apply -f traefik-dashboard.yml
k apply -f traefik-ingress-controller.yml
