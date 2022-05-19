package jpabook.start;

import lombok.Getter;
import lombok.Setter;

import javax.persistence.*;

@Getter
@Setter
@Entity
@Table(name="THEATERS")
public class Theaters {
    @Id
    @GeneratedValue
    @Column(name="THEATER_ID")
    private long id;

    @Column(name="NAME")
    private String name;

    @Column(name="FLOOR")
    private int floor;
}
