package jpabook.start;

import com.sun.istack.NotNull;
import lombok.Getter;
import lombok.Setter;

import javax.persistence.*;

@Getter
@Setter
@Entity
@Table(name="SEATS")
public class Seats {
    @Id
    @GeneratedValue
    @Column(name="SEAT_ID")
    private long id;

    @NotNull
    @Column(name="ROW_")
    private int row;

    @NotNull
    @Column(name="COLUMN_")
    private int column;

    @Column(name="STATUS")
    private String status;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name="THEATER_ID")
    private Theaters theaters;

    public void printInfo() {
        System.out.println("좌석(행/열/상태/상영관) : "+this.row+"/"+this.column+"/"+this.status+"/"+this.theaters.getName());
    }
}