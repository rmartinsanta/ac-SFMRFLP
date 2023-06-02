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
        // Max exec time --> reference time * 10
        return TimeUtil.convert(nanos, TimeUnit.NANOSECONDS, TimeUnit.MILLISECONDS);
    }
}
