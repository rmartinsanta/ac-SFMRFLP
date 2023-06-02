package es.urjc.etsii.grafo.CAP;

import es.urjc.etsii.grafo.experiment.reference.ReferenceResult;
import es.urjc.etsii.grafo.experiment.reference.ReferenceResultProvider;
import org.apache.commons.collections4.map.HashedMap;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Map;

public class CAPReferenceResults extends ReferenceResultProvider {

    private final static String filename = "sota.tsv";
    private final static String separator = "\t";

    Map<String, ReferenceResult> sotaResults = new HashedMap<>();

    public CAPReferenceResults() throws IOException {
        Files.lines(Path.of(filename)).forEach(l -> {
            var parts = l.split(separator);
            var referenceResult = new ReferenceResult();
            referenceResult.setScore(parts[1]);
            referenceResult.setTimeInSeconds(parts[2]);
            sotaResults.put(parts[0], referenceResult);
        });
    }

    @Override
    public ReferenceResult getValueFor(String instanceName) {
        return this.sotaResults.getOrDefault(instanceName, new ReferenceResult());
    }

    @Override
    public String getProviderName() {
        return "PaperResults";
    }
}

