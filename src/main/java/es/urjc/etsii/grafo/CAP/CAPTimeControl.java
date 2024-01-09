package es.urjc.etsii.grafo.CAP;

import es.urjc.etsii.grafo.CAP.model.CAPInstance;
import es.urjc.etsii.grafo.CAP.model.CAPSolution;
import es.urjc.etsii.grafo.algorithms.Algorithm;
import es.urjc.etsii.grafo.services.TimeLimitCalculator;
import es.urjc.etsii.grafo.util.TimeUtil;

import java.util.concurrent.TimeUnit;

public class CAPTimeControl extends TimeLimitCalculator<CAPSolution, CAPInstance> {

    private final CAPReferenceResults referenceResults;

    public CAPTimeControl(CAPReferenceResults referenceResults) {
        this.referenceResults = referenceResults;
    }

    @Override
    public long timeLimitInMillis(CAPInstance instance, Algorithm<CAPSolution, CAPInstance> algorithm) {
        var nanos = this.referenceResults.getValueFor(instance.getId()).getTimeInNanos();
        var timelimit = TimeUtil.convert(nanos, TimeUnit.NANOSECONDS, TimeUnit.MILLISECONDS) * 2;
        return Math.max(1_000, timelimit); // If the timelimit is really small, use 1 second as timelimit.
    }
}
