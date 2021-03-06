FROM mastanca/fiuba-tallerify-cpp:latest
ADD . fiuba-taller2-tallerify-app-server
ARG coveralls_token=dummy
ARG travis_service=false
ENV COVERALLS_REPO_TOKEN=$coveralls_token
ENV COVERALLS_SERVICE_NAME=$travis_service

WORKDIR fiuba-taller2-tallerify-app-server
WORKDIR build
RUN $HOME/usr/bin/cmake -DCOVERALLS=OFF -DCMAKE_BUILD_TYPE=Debug ..
RUN make

CMD ["./fiuba_taller2_tallerify_app_server", "0.0.0.0"]
