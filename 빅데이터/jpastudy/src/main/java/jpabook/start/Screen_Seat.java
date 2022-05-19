package jpabook.start;

import lombok.Getter;
import lombok.Setter;

import javax.persistence.*;

@Getter
@Setter
@Entity
@Table(name = "SCREEN_SEAT")
public class Screen_Seat {
    @Id
    @GeneratedValue
    @Column(name = "TICKET_SEAT_ID")
    private long id;


    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "SEAT_ID")
    private Seats seats;


    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "TICKET_ID")
    private Tickets tickets;
}