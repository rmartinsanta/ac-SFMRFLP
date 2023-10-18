package es.urjc.etsii.grafo.CAP.experiment;

import es.urjc.etsii.grafo.CAP.model.CAPInstance;
import es.urjc.etsii.grafo.CAP.model.CAPSolution;
import es.urjc.etsii.grafo.algorithms.Algorithm;
import es.urjc.etsii.grafo.algorithms.multistart.MultiStartAlgorithm;
import es.urjc.etsii.grafo.autoconfig.irace.AutomaticAlgorithmBuilder;
import es.urjc.etsii.grafo.experiment.AbstractExperiment;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class FinalExperiment extends AbstractExperiment<CAPSolution, CAPInstance> {

    private final AutomaticAlgorithmBuilder<CAPSolution, CAPInstance> builder;

    public FinalExperiment(AutomaticAlgorithmBuilder<CAPSolution, CAPInstance> algorithmBuilder) {
        this.builder = algorithmBuilder;
    }

    @Override

    public List<Algorithm<CAPSolution, CAPInstance>> getAlgorithms() {
        var algorithms = new ArrayList<Algorithm<CAPSolution, CAPInstance>>();

        String[] iraceOutput = """
                
                """.split("\n");

        algorithms.add(sotaAlgorithm());
        for (int i = 0; i < iraceOutput.length; i++) {
            if (!iraceOutput[i].isBlank()) {
                var algorithm = builder.buildFromStringParams(iraceOutput[i].trim());
                // Wrap algorithms as multistart with "infinite" iterations, so we are consistent with the autoconfig engine.
                // Algorithms will automatically stop when they reach the timelimit for a given instance
                var multistart = new MultiStartAlgorithm<>("ac"+i, algorithm, 1_000_000, 1_000_000, 1_000_000);
                algorithms.add(multistart);
            }
        }

        return algorithms;
    }

    public Algorithm<CAPSolution, CAPInstance> sotaAlgorithm(){
//        var constructive = new CAPConstructive("greedyB2", 0.5);
//        var ls = new CAPLS("ext_fhi");
//        var shake = new CAPShake("2");
//        VNS.KMapper<CAPSolution, CAPInstance> kMapper = (s, k) -> k > 5? VNS.KMapper.STOPNOW: k;
//        var bvnsAlberto = new VNS<>("BVNSReimplementation", kMapper, constructive, shake, ls);
//
//        return bvnsAlberto;
        throw new UnsupportedOperationException();
    }
}
