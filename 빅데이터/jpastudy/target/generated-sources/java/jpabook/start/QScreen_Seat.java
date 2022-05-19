package jpabook.start;

import static com.querydsl.core.types.PathMetadataFactory.*;

import com.querydsl.core.types.dsl.*;

import com.querydsl.core.types.PathMetadata;
import javax.annotation.Generated;
import com.querydsl.core.types.Path;
import com.querydsl.core.types.dsl.PathInits;


/**
 * QScreen_Seat is a Querydsl query type for Screen_Seat
 */
@Generated("com.querydsl.codegen.EntitySerializer")
public class QScreen_Seat extends EntityPathBase<Screen_Seat> {

    private static final long serialVersionUID = -1342633918L;

    private static final PathInits INITS = PathInits.DIRECT2;

    public static final QScreen_Seat screen_Seat = new QScreen_Seat("screen_Seat");

    public final NumberPath<Long> id = createNumber("id", Long.class);

    public final QSeats seats;

    public final QTickets tickets;

    public QScreen_Seat(String variable) {
        this(Screen_Seat.class, forVariable(variable), INITS);
    }

    public QScreen_Seat(Path<? extends Screen_Seat> path) {
        this(path.getType(), path.getMetadata(), PathInits.getFor(path.getMetadata(), INITS));
    }

    public QScreen_Seat(PathMetadata metadata) {
        this(metadata, PathInits.getFor(metadata, INITS));
    }

    public QScreen_Seat(PathMetadata metadata, PathInits inits) {
        this(Screen_Seat.class, metadata, inits);
    }

    public QScreen_Seat(Class<? extends Screen_Seat> type, PathMetadata metadata, PathInits inits) {
        super(type, metadata, inits);
        this.seats = inits.isInitialized("seats") ? new QSeats(forProperty("seats"), inits.get("seats")) : null;
        this.tickets = inits.isInitialized("tickets") ? new QTickets(forProperty("tickets"), inits.get("tickets")) : null;
    }

}

