package jpabook.start;

import lombok.Getter;
import lombok.Setter;

import javax.persistence.*;
import java.util.Date;

@Getter
@Setter
@Entity
@Table(name="MOVIES")
public class Movies extends BaseEntity {
    @Id
    @GeneratedValue
    @Column(name="MOVIE_ID")
    private long id;

    @Column(name="NAME")
    private String name;

    @Temporal(TemporalType.DATE)
    private Date openingDate;

    @Column(name="GENRE")
    private Genre genre;

    @Column(name="RUNNING_TIME")
    private int runningTime;

    public void PrintInfo(){
        System.out.println("-".repeat(40));
        System.out.println("영화의 이름은 " + this.getName());
        System.out.println("영화의 장르는 " + this.getGenre());
        System.out.println("영화의 공개일은 " + this.getOpeningDate());
        System.out.println("영화의 상영시간은 " + this.getRunningTime() + "min");
        System.out.println("-".repeat(40));
    }
}