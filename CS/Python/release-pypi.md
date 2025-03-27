# Pypi Release Steps
> with poetry

## Steps

```shell
poetry new xxxx-sdk-py

poetry build

poetry config repositories.<reponame> https://addr/
poetry config http-basic.foo-pub <username> <password>

poetry publish -r <reponame>
poetry publish --build --repository <reponame>

```
