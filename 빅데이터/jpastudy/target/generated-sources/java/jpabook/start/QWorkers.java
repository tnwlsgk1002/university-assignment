package jpabook.start;

import static com.querydsl.core.types.PathMetadataFactory.*;

import com.querydsl.core.types.dsl.*;

import com.querydsl.core.types.PathMetadata;
import javax.annotation.Generated;
import com.querydsl.core.types.Path;


/**
 * QWorkers is a Querydsl query type for Workers
 */
@Generated("com.querydsl.codegen.EntitySerializer")
public class QWorkers extends EntityPathBase<Workers> {

    private static final long serialVersionUID = 340863967L;

    public static final QWorkers workers = new QWorkers("workers");

    public final NumberPath<Integer> age = createNumber("age", Integer.class);

    public final NumberPath<Long> id = createNumber("id", Long.class);

    public final StringPath name = createString("name");

    public QWorkers(String variable) {
        super(Workers.class, forVariable(variable));
    }

    public QWorkers(Path<? extends Workers> path) {
        super(path.getType(), path.getMetadata());
    }

    public QWorkers(PathMetadata metadata) {
        super(Workers.class, metadata);
    }

}

