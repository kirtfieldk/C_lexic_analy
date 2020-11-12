
# Build on top of frolvlad/alpine-gcc, which is alpine linux with a gcc c compiler 

FROM frolvlad/alpine-gcc

# Install nano text editor 
RUN apk add nano

# Install SBCL (we've got to add the URL the package is located at to the package manager before installation)
RUN cd /etc/apk &&\
    echo 'http://dl-cdn.alpinelinux.org/alpine/edge/community/' >> repositories &&\
    apk update &&\
    apk add sbcl

# set a directory for the container 
WORKDIR /home/403

# download the givens tarball
ADD https://github.com/zwhittenVCU/403Docker/blob/master/givens.tar.gz?raw=true /home/403/

# uncompress the givens tarball & delete it 
RUN cd /home/403 &&\
    tar -xvzf givens.tar.gz &&\
    rm givens.tar.gz

# run our shell 
CMD ["/bin/ash"]