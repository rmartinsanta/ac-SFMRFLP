package es.urjc.etsii.grafo.CAP.experiment;

import es.urjc.etsii.grafo.CAP.components.CAPConstructive;
import es.urjc.etsii.grafo.CAP.components.CAPLS;
import es.urjc.etsii.grafo.CAP.components.CAPShake;
import es.urjc.etsii.grafo.CAP.model.CAPInstance;
import es.urjc.etsii.grafo.CAP.model.CAPSolution;
import es.urjc.etsii.grafo.algorithms.Algorithm;
import es.urjc.etsii.grafo.algorithms.VNS;
import es.urjc.etsii.grafo.algorithms.multistart.MultiStartAlgorithm;
import es.urjc.etsii.grafo.autoconfig.irace.AutomaticAlgorithmBuilder;
import es.urjc.etsii.grafo.experiment.AbstractExperiment;

import java.util.List;
import java.util.stream.Collectors;

public class IraceResultExperiment extends AbstractExperiment<CAPSolution, CAPInstance> {

    private final AutomaticAlgorithmBuilder<CAPSolution, CAPInstance> algorithmBuilder;

    public IraceResultExperiment(AutomaticAlgorithmBuilder<CAPSolution, CAPInstance> algorithmBuilder) {
        this.algorithmBuilder = algorithmBuilder;
    }

    @Override

    public List<Algorithm<CAPSolution, CAPInstance>> getAlgorithms() {
        // ROOT=IteratedGreedy ROOT_IteratedGreedy.constructive=CAPConstructive ROOT_IteratedGreedy.constructive_CAPConstructive.alpha=0.26 ROOT_IteratedGreedy.constructive_CAPConstructive.type='"greedyB1"' ROOT_IteratedGreedy.destructionReconstruction=CAPShake ROOT_IteratedGreedy.destructionReconstruction_CAPShake.type='"7"' ROOT_IteratedGreedy.improver=VND ROOT_IteratedGreedy.improver_VND.improver1=SequentialImprover ROOT_IteratedGreedy.improver_VND.improver1_SequentialImprover.improverA=CAPLS ROOT_IteratedGreedy.improver_VND.improver1_SequentialImprover.improverA_CAPLS.type='"ins_hi"' ROOT_IteratedGreedy.improver_VND.improver1_SequentialImprover.improverB=CAPLS ROOT_IteratedGreedy.improver_VND.improver1_SequentialImprover.improverB_CAPLS.type='"ext_fhi"' ROOT_IteratedGreedy.improver_VND.improver2=VND ROOT_IteratedGreedy.improver_VND.improver2_VND.improver1=NullImprover ROOT_IteratedGreedy.improver_VND.improver2_VND.improver2=NullImprover ROOT_IteratedGreedy.improver_VND.improver2_VND.improver3=NullImprover ROOT_IteratedGreedy.improver_VND.improver3=VND ROOT_IteratedGreedy.improver_VND.improver3_VND.improver1=NullImprover ROOT_IteratedGreedy.improver_VND.improver3_VND.improver2=NullImprover ROOT_IteratedGreedy.improver_VND.improver3_VND.improver3=NullImprover ROOT_IteratedGreedy.maxIterations=603212323 ROOT_IteratedGreedy.stopIfNotImprovedIn=83780066
        //var myAlgorithm = algorithmBuilder.buildFromStringParams("ROOT=IteratedGreedy ROOT_IteratedGreedy.constructive=CAPConstructive ROOT_IteratedGreedy.constructive_CAPConstructive.alpha=0.4 ROOT_IteratedGreedy.constructive_CAPConstructive.type='\"greedyB1\"' ROOT_IteratedGreedy.destructionReconstruction=CAPShake ROOT_IteratedGreedy.destructionReconstruction_CAPShake.type='\"7\"' ROOT_IteratedGreedy.improver=VND ROOT_IteratedGreedy.improver_VND.improver1=SequentialImprover ROOT_IteratedGreedy.improver_VND.improver1_SequentialImprover.improverA=CAPLS ROOT_IteratedGreedy.improver_VND.improver1_SequentialImprover.improverA_CAPLS.type='\"ins_hi\"' ROOT_IteratedGreedy.improver_VND.improver1_SequentialImprover.improverB=CAPLS ROOT_IteratedGreedy.improver_VND.improver1_SequentialImprover.improverB_CAPLS.type='\"ext_fhi\"' ROOT_IteratedGreedy.improver_VND.improver2=VND ROOT_IteratedGreedy.improver_VND.improver2_VND.improver1=NullImprover ROOT_IteratedGreedy.improver_VND.improver2_VND.improver2=NullImprover ROOT_IteratedGreedy.improver_VND.improver2_VND.improver3=NullImprover ROOT_IteratedGreedy.improver_VND.improver3=VND ROOT_IteratedGreedy.improver_VND.improver3_VND.improver1=NullImprover ROOT_IteratedGreedy.improver_VND.improver3_VND.improver2=NullImprover ROOT_IteratedGreedy.improver_VND.improver3_VND.improver3=NullImprover ROOT_IteratedGreedy.maxIterations=492395214 ROOT_IteratedGreedy.stopIfNotImprovedIn=718905815");
        //var oldIraceAlgorithm = algorithmBuilder.buildFromStringParams("ROOT=IteratedGreedy ROOT_IteratedGreedy.constructive=CAPConstructive ROOT_IteratedGreedy.constructive_CAPConstructive.alpha=0.4 ROOT_IteratedGreedy.constructive_CAPConstructive.type='\"greedyB1\"' ROOT_IteratedGreedy.destructionReconstruction=CAPShake ROOT_IteratedGreedy.destructionReconstruction_CAPShake.type='\"7\"' ROOT_IteratedGreedy.improver=VND ROOT_IteratedGreedy.improver_VND.improver1=SequentialImprover ROOT_IteratedGreedy.improver_VND.improver1_SequentialImprover.improverA=CAPLS ROOT_IteratedGreedy.improver_VND.improver1_SequentialImprover.improverA_CAPLS.type='\"ins_hi\"' ROOT_IteratedGreedy.improver_VND.improver1_SequentialImprover.improverB=CAPLS ROOT_IteratedGreedy.improver_VND.improver1_SequentialImprover.improverB_CAPLS.type='\"ext_fhi\"' ROOT_IteratedGreedy.improver_VND.improver2=VND ROOT_IteratedGreedy.improver_VND.improver2_VND.improver1=NullImprover ROOT_IteratedGreedy.improver_VND.improver2_VND.improver2=NullImprover ROOT_IteratedGreedy.improver_VND.improver2_VND.improver3=NullImprover ROOT_IteratedGreedy.improver_VND.improver3=VND ROOT_IteratedGreedy.improver_VND.improver3_VND.improver1=NullImprover ROOT_IteratedGreedy.improver_VND.improver3_VND.improver2=NullImprover ROOT_IteratedGreedy.improver_VND.improver3_VND.improver3=NullImprover ROOT_IteratedGreedy.maxIterations=492395214 ROOT_IteratedGreedy.stopIfNotImprovedIn=1000");

        // Se utilizan el top 3 de configuraciones de Irace: 5248, 4591, 5207

        var algorithms = List.of(
//                oldIraceAlgorithm,
                algorithmBuilder.buildFromStringParams("ROOT=IteratedGreedy ROOT_IteratedGreedy.constructive=CAPConstructive ROOT_IteratedGreedy.constructive_CAPConstructive.alpha=0.93 ROOT_IteratedGreedy.constructive_CAPConstructive.type='\"greedyB2\"' ROOT_IteratedGreedy.destructionReconstruction=CAPShake ROOT_IteratedGreedy.destructionReconstruction_CAPShake.type='\"1\"' ROOT_IteratedGreedy.improver=SequentialImprover ROOT_IteratedGreedy.improver_SequentialImprover.improverA=CAPLS ROOT_IteratedGreedy.improver_SequentialImprover.improverA_CAPLS.type='\"ins_bi\"' ROOT_IteratedGreedy.improver_SequentialImprover.improverB=SequentialImprover ROOT_IteratedGreedy.improver_SequentialImprover.improverB_SequentialImprover.improverA=NullImprover ROOT_IteratedGreedy.improver_SequentialImprover.improverB_SequentialImprover.improverB=CAPLS ROOT_IteratedGreedy.improver_SequentialImprover.improverB_SequentialImprover.improverB_CAPLS.type='\"exc_bi\"' ROOT_IteratedGreedy.maxIterations=535158 ROOT_IteratedGreedy.stopIfNotImprovedIn=664797"), // <-- Este segun el Excel
                algorithmBuilder.buildFromStringParams("ROOT=IteratedGreedy ROOT_IteratedGreedy.constructive=CAPConstructive ROOT_IteratedGreedy.constructive_CAPConstructive.alpha=0.82 ROOT_IteratedGreedy.constructive_CAPConstructive.type='\"greedyB2\"' ROOT_IteratedGreedy.destructionReconstruction=CAPShake ROOT_IteratedGreedy.destructionReconstruction_CAPShake.type='\"1\"' ROOT_IteratedGreedy.improver=SequentialImprover ROOT_IteratedGreedy.improver_SequentialImprover.improverA=CAPLS ROOT_IteratedGreedy.improver_SequentialImprover.improverA_CAPLS.type='\"ins_bi\"' ROOT_IteratedGreedy.improver_SequentialImprover.improverB=SequentialImprover ROOT_IteratedGreedy.improver_SequentialImprover.improverB_SequentialImprover.improverA=NullImprover ROOT_IteratedGreedy.improver_SequentialImprover.improverB_SequentialImprover.improverB=CAPLS ROOT_IteratedGreedy.improver_SequentialImprover.improverB_SequentialImprover.improverB_CAPLS.type='\"exc_bi\"' ROOT_IteratedGreedy.maxIterations=821708 ROOT_IteratedGreedy.stopIfNotImprovedIn=370635"),
                algorithmBuilder.buildFromStringParams("ROOT=IteratedGreedy ROOT_IteratedGreedy.constructive=CAPConstructive ROOT_IteratedGreedy.constructive_CAPConstructive.alpha=0.82 ROOT_IteratedGreedy.constructive_CAPConstructive.type='\"greedyB2\"' ROOT_IteratedGreedy.destructionReconstruction=CAPShake ROOT_IteratedGreedy.destructionReconstruction_CAPShake.type='\"1\"' ROOT_IteratedGreedy.improver=SequentialImprover ROOT_IteratedGreedy.improver_SequentialImprover.improverA=CAPLS ROOT_IteratedGreedy.improver_SequentialImprover.improverA_CAPLS.type='\"ins_bi\"' ROOT_IteratedGreedy.improver_SequentialImprover.improverB=SequentialImprover ROOT_IteratedGreedy.improver_SequentialImprover.improverB_SequentialImprover.improverA=NullImprover ROOT_IteratedGreedy.improver_SequentialImprover.improverB_SequentialImprover.improverB=CAPLS ROOT_IteratedGreedy.improver_SequentialImprover.improverB_SequentialImprover.improverB_CAPLS.type='\"exc_bi\"' ROOT_IteratedGreedy.maxIterations=464301 ROOT_IteratedGreedy.stopIfNotImprovedIn=477392"),
                getSOTAAlgorithm()
        );

        return algorithms.stream().map(a -> new MultiStartAlgorithm<>(a.getShortName(), a, 1_000_000, 1_000_000, 1_000_000)).collect(Collectors.toList());
    }

    public Algorithm<CAPSolution, CAPInstance> getSOTAAlgorithm(){
        // Algoritmo de alberto en el paper
        var constructive = new CAPConstructive("greedyB2", 0.5);
        var ls = new CAPLS("ext_fhi");
        var shake = new CAPShake("2");
        VNS.KMapper<CAPSolution, CAPInstance> kMapper = (s, k) -> k > 5? VNS.KMapper.STOPNOW: k;
        var bvnsAlberto = new VNS<>("BVNSReimplementation", kMapper, constructive, shake, ls);

        return bvnsAlberto;
    }
}
