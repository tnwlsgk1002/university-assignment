package jpabook.start;

import lombok.Getter;
import lombok.Setter;

import javax.persistence.*;
import java.util.ArrayList;
import java.util.List;

@Getter
@Setter
@Entity
@Table(name="MOVIE_WORKER")
public class Movie_Worker {
    @Id
    @GeneratedValue
    @Column(name="MOVIE_WORKER_ID")
    private long id;

    @Enumerated(EnumType.STRING)
    private Role_Type role_type;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name="MOVIE_ID")
    private Movies movie;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name="WORKER_ID")
    private Workers worker;

    public void PrintInfo(){
        System.out.println("-".repeat(40));
        System.out.println("감독/출연(" + this.id + ")의 이름은 " + this.getWorker().getName());
        System.out.println("감독/출연(" + this.id + ")의 역할은 " + this.getRole_type());
        System.out.println("감독/출연(" + this.id + ")의 나이는 " + this.getWorker().getAge());
        System.out.println("-".repeat(40));
    }
}