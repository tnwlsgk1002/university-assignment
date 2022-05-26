package jpabook.start;

import static com.querydsl.core.types.PathMetadataFactory.*;

import com.querydsl.core.types.dsl.*;

import com.querydsl.core.types.PathMetadata;
import javax.annotation.Generated;
import com.querydsl.core.types.Path;


/**
 * QActors is a Querydsl query type for Actors
 */
@Generated("com.querydsl.codegen.EntitySerializer")
public class QActors extends EntityPathBase<Actors> {

    private static final long serialVersionUID = -768411468L;

    public static final QActors actors = new QActors("actors");

    public final QWorkers _super = new QWorkers(this);

    //inherited
    public final NumberPath<Integer> age = _super.age;

    public final NumberPath<Integer> height = createNumber("height", Integer.class);

    //inherited
    public final NumberPath<Long> id = _super.id;

    public final StringPath instaId = createString("instaId");

    //inherited
    public final StringPath name = _super.name;

    public QActors(String variable) {
        super(Actors.class, forVariable(variable));
    }

    public QActors(Path<? extends Actors> path) {
        super(path.getType(), path.getMetadata());
    }

    public QActors(PathMetadata metadata) {
        super(Actors.class, metadata);
    }

}

