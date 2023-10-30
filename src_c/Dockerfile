FROM alpine:3

COPY . /home
WORKDIR /home
RUN find . -name '.DS_Store' -type f -delete

WORKDIR /home/1_code/build
RUN apk add build-base
RUN apk add cmake
RUN cmake ..
RUN make

WORKDIR /home/2_instances
RUN apk add python3
RUN apk add py3-pip
RUN apk add py3-scikit-learn=1.2.2-r1
RUN pip install -r requirements_docker.txt

WORKDIR /home/3_irace
RUN apk add R
RUN R -e 'install.packages("irace",repos="https://cran.r-project.org")'
RUN chmod +x target-runner

WORKDIR /home/4_experiments
CMD ["/bin/sh"]
