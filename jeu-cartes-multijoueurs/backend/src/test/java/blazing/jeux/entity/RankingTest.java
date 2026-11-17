package blazing.jeux.entity;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class RankingTest {

    @Test
    void nouveauRanking_valeursZeroParDefaut() {
        Ranking ranking = new Ranking();
        assertEquals(0, ranking.getTotalGames());
        assertEquals(0, ranking.getTotalWins());
        assertEquals(0, ranking.getTotalLosses());
    }

    @Test
    void setTotalWins_retourneCorrectement() {
        Ranking ranking = new Ranking();
        ranking.setTotalWins(5);
        assertEquals(5, ranking.getTotalWins());
    }

    @Test
    void setTotalLosses_retourneCorrectement() {
        Ranking ranking = new Ranking();
        ranking.setTotalLosses(3);
        assertEquals(3, ranking.getTotalLosses());
    }

    @Test
    void setTotalGames_retourneCorrectement() {
        Ranking ranking = new Ranking();
        ranking.setTotalGames(8);
        assertEquals(8, ranking.getTotalGames());
    }

    @Test
    void incrementerVictoires_manuellement() {
        Ranking ranking = new Ranking();
        ranking.setTotalWins(2);
        ranking.setTotalGames(3);

        // Simule ce que fait RankingService.recordWin()
        ranking.setTotalWins(ranking.getTotalWins() + 1);
        ranking.setTotalGames(ranking.getTotalGames() + 1);

        assertEquals(3, ranking.getTotalWins());
        assertEquals(4, ranking.getTotalGames());
        assertEquals(0, ranking.getTotalLosses()); // inchangé
    }

    @Test
    void incrementerDefaites_manuellement() {
        Ranking ranking = new Ranking();
        ranking.setTotalLosses(1);
        ranking.setTotalGames(2);

        // Simule ce que fait RankingService.recordLoss()
        ranking.setTotalLosses(ranking.getTotalLosses() + 1);
        ranking.setTotalGames(ranking.getTotalGames() + 1);

        assertEquals(2, ranking.getTotalLosses());
        assertEquals(3, ranking.getTotalGames());
        assertEquals(0, ranking.getTotalWins()); // inchangé
    }

    @Test
    void setPlayer_lieBienLeJoueur() {
        Ranking ranking = new Ranking();
        Player player = new Player();
        player.setUsername("alice");
        ranking.setPlayer(player);
        assertEquals("alice", ranking.getPlayer().getUsername());
    }
}