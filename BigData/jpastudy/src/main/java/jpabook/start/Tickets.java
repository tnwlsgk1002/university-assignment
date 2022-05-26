package jpabook.start;

import lombok.Getter;
import lombok.Setter;

import javax.persistence.*;

@Getter
@Setter
@Entity
@Table(name = "TICKETS")
public class Tickets {
    @Id
    @GeneratedValue
    @Column(name = "TICKET_ID")
    private long id;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "SCREEN_ID")
    private Screens screen;

    public void setScreens(Screens screen) {
        this.screen = screen;
        if (!screen.getTickets().contains(this)) {
            screen.getTickets().add(this);
        }
    }

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "USER_ID")
    private Users user;

    public void setUsers(Users user) {
        this.user = user;
        if (!user.getTickets().contains(this)) {
            user.getTickets().add(this);
        }
    }
}
