package jpabook.start;

import static com.querydsl.core.types.PathMetadataFactory.*;

import com.querydsl.core.types.dsl.*;

import com.querydsl.core.types.PathMetadata;
import javax.annotation.Generated;
import com.querydsl.core.types.Path;
import com.querydsl.core.types.dsl.PathInits;


/**
 * QMovie_Worker is a Querydsl query type for Movie_Worker
 */
@Generated("com.querydsl.codegen.EntitySerializer")
public class QMovie_Worker extends EntityPathBase<Movie_Worker> {

    private static final long serialVersionUID = 408576675L;

    private static final PathInits INITS = PathInits.DIRECT2;

    public static final QMovie_Worker movie_Worker = new QMovie_Worker("movie_Worker");

    public final NumberPath<Long> id = createNumber("id", Long.class);

    public final QMovies movie;

    public final EnumPath<Role_Type> role_type = createEnum("role_type", Role_Type.class);

    public final QWorkers worker;

    public QMovie_Worker(String variable) {
        this(Movie_Worker.class, forVariable(variable), INITS);
    }

    public QMovie_Worker(Path<? extends Movie_Worker> path) {
        this(path.getType(), path.getMetadata(), PathInits.getFor(path.getMetadata(), INITS));
    }

    public QMovie_Worker(PathMetadata metadata) {
        this(metadata, PathInits.getFor(metadata, INITS));
    }

    public QMovie_Worker(PathMetadata metadata, PathInits inits) {
        this(Movie_Worker.class, metadata, inits);
    }

    public QMovie_Worker(Class<? extends Movie_Worker> type, PathMetadata metadata, PathInits inits) {
        super(type, metadata, inits);
        this.movie = inits.isInitialized("movie") ? new QMovies(forProperty("movie")) : null;
        this.worker = inits.isInitialized("worker") ? new QWorkers(forProperty("worker")) : null;
    }

}

