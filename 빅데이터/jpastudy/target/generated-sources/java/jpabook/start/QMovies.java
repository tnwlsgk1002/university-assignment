package jpabook.start;

import static com.querydsl.core.types.PathMetadataFactory.*;

import com.querydsl.core.types.dsl.*;

import com.querydsl.core.types.PathMetadata;
import javax.annotation.Generated;
import com.querydsl.core.types.Path;


/**
 * QMovies is a Querydsl query type for Movies
 */
@Generated("com.querydsl.codegen.EntitySerializer")
public class QMovies extends EntityPathBase<Movies> {

    private static final long serialVersionUID = -413725991L;

    public static final QMovies movies = new QMovies("movies");

    public final QBaseEntity _super = new QBaseEntity(this);

    //inherited
    public final DateTimePath<java.time.LocalDateTime> createdDate = _super.createdDate;

    public final EnumPath<Genre> genre = createEnum("genre", Genre.class);

    public final NumberPath<Long> id = createNumber("id", Long.class);

    //inherited
    public final DateTimePath<java.time.LocalDateTime> lastModifiedDate = _super.lastModifiedDate;

    public final StringPath name = createString("name");

    public final DatePath<java.util.Date> openingDate = createDate("openingDate", java.util.Date.class);

    public final NumberPath<Integer> runningTime = createNumber("runningTime", Integer.class);

    public QMovies(String variable) {
        super(Movies.class, forVariable(variable));
    }

    public QMovies(Path<? extends Movies> path) {
        super(path.getType(), path.getMetadata());
    }

    public QMovies(PathMetadata metadata) {
        super(Movies.class, metadata);
    }

}

