package es.urjc.etsii.grafo.CAP.model;

import es.urjc.etsii.grafo.solution.LazyMove;

/**
 * Base class for all movements for the CAP problem. All movements should extend this class.
 */
public abstract class CAPBaseMove extends LazyMove<CAPSolution, CAPInstance> {

    /**
     * Move constructor
     * @param solution solution
     */
    public CAPBaseMove(CAPSolution solution) {
        super(solution);
    }

    /**
     * Executes the proposed move,
     * to be implemented by each move type.
     * @param solution Solution where this move will be applied to.
     * @return true if the solution has changed,
     * false if for any reason the movement is not applied or the solution does not change after executing the move
     */
    @Override
    protected abstract boolean _execute(CAPSolution solution);

    /**
     * Get the movement value, represents how much does the move changes the f.o of a solution if executed
     *
     * @return f.o change
     */
    public abstract double getValue();

    /**
     * Get next move in this sequence.
     * There are two main strategies to generate moves:
     * - eagerly: all at once, and store them on a list
     * - lazily: only under demand, using Streams, like an Iterator
     * Only the second implementation requires implementing this method. Ignore this method if using the first one.
     *
     * @param solution solution used to generate the previous move,
     *                and where data will be picked for the current move
     * @return the next move in this generator sequence if there is a next move, return null to signal end of sequence.
     */
    @Override
    public LazyMove<CAPSolution, CAPInstance> next(CAPSolution solution) {
        throw new UnsupportedOperationException("Not implemented");
    }

    /**
     * Returns a String representation of the current movement. Only use relevant fields.
     * Tip: Default IntelliJ implementation is fine
     *
     * @return human readable string
     */
    public abstract String toString();

    /** {@inheritDoc} */
    @Override
    public abstract boolean equals(Object o);

    /** {@inheritDoc} */
    @Override
    public abstract int hashCode();

}
