package jpabook.start;

import static com.querydsl.core.types.PathMetadataFactory.*;

import com.querydsl.core.types.dsl.*;

import com.querydsl.core.types.PathMetadata;
import javax.annotation.Generated;
import com.querydsl.core.types.Path;


/**
 * QDirectors is a Querydsl query type for Directors
 */
@Generated("com.querydsl.codegen.EntitySerializer")
public class QDirectors extends EntityPathBase<Directors> {

    private static final long serialVersionUID = -905835759L;

    public static final QDirectors directors = new QDirectors("directors");

    public final QWorkers _super = new QWorkers(this);

    //inherited
    public final NumberPath<Integer> age = _super.age;

    public final StringPath birthPlace = createString("birthPlace");

    //inherited
    public final NumberPath<Long> id = _super.id;

    //inherited
    public final StringPath name = _super.name;

    public QDirectors(String variable) {
        super(Directors.class, forVariable(variable));
    }

    public QDirectors(Path<? extends Directors> path) {
        super(path.getType(), path.getMetadata());
    }

    public QDirectors(PathMetadata metadata) {
        super(Directors.class, metadata);
    }

}

