# Requires libcurl4-openssl-dev in most Ubuntu distributions, install before launching
set -e
mvn clean package
java \
-Xmx24G \
-Xms24G \
-jar target/SFMRFLP-0.19-SNAPSHOT.jar \
--serializers.solution-json.enabled=true \
--serializers.solution-json.frequency=all \
--solver.experiments=FinalExperiment \
--solver.parallelExecutor=true \
--solver.nWorkers=8 \
--solver.metrics=true
