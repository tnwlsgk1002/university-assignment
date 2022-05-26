package jpabook.start;

import lombok.Getter;
import lombok.Setter;

import javax.persistence.*;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

// 상영
@Getter
@Setter
@Entity
@Table(name="SCREENS")
public class Screens {
    @Id
    @GeneratedValue
    @Column(name="SCREEN_ID")
    private long id;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name="THEATER_ID")
    private Theaters theater;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name="MOVIE_ID")
    private Movies movie;

    @OneToMany(mappedBy = "screen", cascade = CascadeType.ALL)
    private List<Tickets> tickets = new ArrayList<Tickets>();

    public void addTicket(Tickets ticket) {
        this.tickets.add(ticket);
        if (ticket.getScreen()!=this) {
            ticket.setScreen(this);
        }
    }

    @Temporal(TemporalType.TIMESTAMP)
    private Date startTime;

    @Temporal(TemporalType.TIMESTAMP)
    private Date endTime;

    public void printInfo() {
        System.out.println("해당 상영의 영화이름/시작시간/종료시간 : "+this.getMovie().getName()+"/"+this.getStartTime()+"/"+this.getEndTime());
    }
}
