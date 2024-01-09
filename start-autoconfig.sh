# Requires libcurl4-openssl-dev in most Ubuntu distributions, install before launching
set -e
mvn clean package
java \
-Xmx24G \
-Xms24G \
-jar target/SFMRFLP-0.19-SNAPSHOT.jar \
--autoconfig \
--solver.parallelExecutor=true \
--solver.nWorkers=32
