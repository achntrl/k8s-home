# Caveats

The deployment contains 2 images: `addon-resizer` and `kube-state-metrics`. These images
have been built for `amd64` architecture. You need the `arm` images

- [addon-resizer](https://github.com/kubernetes/autoscaler/tree/master/addon-resizer)
- [kube-state-metrics](https://github.com/kubernetes/kube-state-metrics/)

Both of the can be built with the command

```
make container ARCH=arm
```
