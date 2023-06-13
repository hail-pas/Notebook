# Pypi Release Steps
> with poetry

## Steps

```shell
poetry new burnish-sdk-py

poetry build

poetry config repositories.<reponame> https://addr/

poetry publish -r <reponame>

```
